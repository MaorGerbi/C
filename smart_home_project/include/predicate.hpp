#ifndef PREDICATE_H
#define PREDICATE_H

namespace experis {

template <typename KindOfQueue>
class Predicate {
public:
	Predicate(const KindOfQueue& a_queue, size_t a_comparParam);
    bool operator()()const;
    
private:
    const KindOfQueue& m_queue;
	size_t m_comparParam;
};

} //experis

#include "predicate.inl"

#endif //PREDICATE_H

