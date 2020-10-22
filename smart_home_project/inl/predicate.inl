namespace experis {

template <typename KindOfQueue>
Predicate<KindOfQueue>::Predicate(const KindOfQueue& a_queue, size_t a_comparParam)
: m_queue(a_queue)
, m_comparParam(a_comparParam)
{
}

template <typename KindOfQueue>
bool Predicate<KindOfQueue>::operator()()const {
	return m_queue.m_numOfItems == m_comparParam;
}

} //experis

