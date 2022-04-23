#include "../includes/cache.h"

template <typename PageDataT, typename KeyT>
bool Cache<PageDataT, KeyT> :: RequestPage(const KeyT& page_number)
{
    MapIt page = hash_table.find(page_number);
    
    if (page == hash_table.end()) //miss in cache
    {
        InsertPage(page_number);
        return false;
    }

    MovePage(page);
    return true;
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: InsertPage(const KeyT& page_number)
{    
    size_t T1_size = T1.size();
    size_t L1_size = T1_size + B1.size();
    size_t L2_size = T2.size() + B2.size();

    if (L1_size == cache_size)
    {
        if (T1_size < cache_size)
        {
            MapIt B1_last_page = hash_table.find(*(std::prev(B1.end())));
            DeletePage(B1_last_page, B1_);
            Replace_p(NOT_IN_LISTS_);   
        }

        else
        {
            MapIt T1_last_page = hash_table.find(*(std::prev(T1.end())));
            DeletePage(T1_last_page, (T1_last_page->second).list_id);
        }
    }

    else if ((L1_size < cache_size) && (L1_size + L2_size >= cache_size))
    {
        if (L1_size + L2_size == 2*cache_size)
        {
            MapIt B2_last_page = hash_table.find(*(std::prev(B2.end())));
            DeletePage(B2_last_page, B2_);
        }

        Replace_p(NOT_IN_LISTS_);
    }

    T1.push_front(page_number);
    hash_table.insert({page_number, {T1_, T1.begin()}});
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: DeletePage(const MapIt & page, const int & list_number)
{
    switch (list_number)
    {
        case T1_:
            T1.erase((page->second).value);
            break;
        case T2_:
            T2.erase((page->second).value);
            break;
        case B1_:
            B1.erase((page->second).value);
            break;
        case B2_:
            B2.erase((page->second).value);
            break;
        case NOT_IN_LISTS_:
            std::cout << "Error:DeletePage(try to delete unplaced element)" << std::endl;
            break;
        default: 
            break;
    }

    hash_table.erase(page);
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: Replace_p(const int & list_number)
{
    size_t T1_size = T1.size();

    if ((T1_size >= 1) && ((list_number == B2_ && (int) T1_size == p) || ((int) T1_size > p)))
        MoveFromEnd(T1, B1, B1_);
    else
        MoveFromEnd(T2, B2, B2_);
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: InsertToList(const KeyT & page_number, const int & list_number, ListT& list_to)
{
    switch(list_number)
    {
        case NOT_IN_LISTS_:
           list_to.push_front(page_number);
        default:
            std::cout << "Error(InsertToList): page has already in cache. ";
            std::cout << "You need to use MoveToOtherList()" << std::endl;
    }
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: MoveToOtherList(MapIt& page, ListT& list_from, ListT& list_to, const int & list_number)
{
    list_to.push_front(*((page->second).value));
    list_from.erase((page->second).value);

    (page->second).value = list_to.begin();
    (page->second).list_id = (Lists) list_number;
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: MoveFromEnd(ListT& list_from, ListT& list_to, const int & list_number)
{
    MapIt page = hash_table.find(*(std::prev(list_from.end())));
    MoveToOtherList(page, list_from, list_to, list_number);
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: MovePage(MapIt& page)
{
    switch((page->second).list_id)
    {
        case T1_:
            MoveToOtherList(page, T1, T2, T2_);
            return;
        case T2_:
            MoveToOtherList(page, T2, T2, T2_);
            return;
        case B1_:
            p = std::min <size_t> (cache_size, p + std::max <size_t> (B2.size() / B1.size(), 1lu)); 
            Replace_p((page->second).list_id);
            MoveToOtherList(page, B1, T2, T2_);
            return;
        case B2_:
            p = (size_t) std::max <ssize_t> (0l, (ssize_t) p - std::max <size_t> (B1.size() / B2.size(), 1lu));
            Replace_p((page->second).list_id);
            MoveToOtherList(page, B2, T2, T2_);
            return;
        case NOT_IN_LISTS_:
            std::cout << "Error(MovePage): Miss in cache - page is not in lists. ";
            std::cout << "You need to use Insert() in order to insert page" << std::endl;

    }
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: PrintList(const ListT& list, const std::string& list_name) const
{
    std::cout << list_name << ", size = " << list.size() << ":\n";
    for (auto i_elem = list.begin(); i_elem != list.end(); i_elem++)
        std::cout << "\t""Page = " << *(i_elem) << std::endl;
}

template <typename PageDataT, typename KeyT>
void Cache<PageDataT, KeyT> :: PrintInfo() const
{
    std::cout << "Printing status information about cache..." << std::endl;
    std::cout << "p = " << p << ", cache_size = " << cache_size*2 << std::endl;

    PrintList (T1, "T1");
    PrintList (T2, "T2");
    PrintList (B1, "B1");
    PrintList (B2, "B2");

    std::cout << std::endl;
}