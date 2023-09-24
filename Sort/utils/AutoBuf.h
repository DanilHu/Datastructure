#ifndef AUTOBUF_
#define AUTOBUF_

#include <algorithm>
#include <atomic>
#include <cassert>
#include <cstddef>
#include <malloc/_malloc.h>
#include <stdlib.h>
#include <sys/uio.h>

class AutoBuf {
private:
    using size_type = uint32_t; 

    struct LinkNode {
        LinkNode* next {nullptr};
        size_type size {0};
        size_type used {0};
        size_type consumed {0};
        char buf[0];
    };

    static constexpr size_type PAGE_SIZE = 4 * 1024;
    static constexpr size_type PAGE_BUF_SIZE = PAGE_SIZE - sizeof(LinkNode);

    LinkNode* m_head {nullptr};
    LinkNode* m_tail {nullptr};
    size_type m_size {0};

public:
    AutoBuf() = default;

    AutoBuf(const AutoBuf&) = delete;

    AutoBuf(AutoBuf&& obj) {
        m_head = obj.m_head;
        m_tail = obj.m_tail;
        m_size = obj.m_size;

        obj.m_size = 0;
        obj.m_head = obj.m_tail = nullptr;
    }

    ~AutoBuf() {
        Clear();
    }

    bool Append(const char* p, size_type size) {
        if(m_tail && m_tail->used < m_tail->size) {
            size_type freeSize = m_tail->size - m_tail->used;
            size_type copySize = std::min(freeSize, size);

            std::copy_n(p, copySize, m_tail->buf + m_tail->used);
            size -= copySize;
            m_tail->used += copySize;
            m_size += copySize;
            p += copySize;
        }        
        if(size != 0) {
            LinkNode* node;
            if(size <= PAGE_BUF_SIZE) {
                if(posix_memalign((void**)&node, PAGE_SIZE, PAGE_SIZE) != 0) {
                    return false;
                }
                node->size = PAGE_BUF_SIZE;
            } else {
                node = (LinkNode*)malloc(size + sizeof(LinkNode));
                if(node == nullptr) {
                    return false;
                }
                node->size = size;
            }
            std::copy_n(p, size, node->buf);
            node->used = size;
            node->consumed = 0;
            node->next = nullptr;
            m_size += size;
            if(m_tail == nullptr) {
                m_head = m_tail = node;
            } else {
                m_tail->next = node;
                m_tail = node;
            }
        }
        return true;
    }

    void Pop(size_type size) {
        assert(m_size >= size);
        m_size -= size;
        while(size != 0) {
            assert(m_head);
            size_type headSize = m_head->used - m_head->consumed;
            if(size < headSize) {
                m_head->consumed += size; 
                return;
            }
            size -= headSize;
            auto next = m_head->next;
            free(m_head);
            m_head = next;
        }
        if(m_head == nullptr) {
            m_tail = nullptr;
            assert(m_size == 0);
        }
    }

    bool IsEmpty() const {
        return m_size == 0;
    }

    size_type Size() const {
        return m_size;
    }

    void Clear() {
        m_size = 0;
        while(m_head) {
            auto next = m_head->next;
            free(m_head);
            m_head = next;
        }
        m_tail = nullptr;
    }

    int GetIOVec(struct iovec* iov, int iovCnt) const {
        auto node = m_head;
        int i;
        for(i = 0; i < iovCnt && node; i++, node = node->next) {
            iov[i].iov_base = node->buf + node->consumed;
            iov[i].iov_len = node->used - node->consumed;
        }
        return i;
    }
};

#endif