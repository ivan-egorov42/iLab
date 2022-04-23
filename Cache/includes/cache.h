#ifndef CACHE_HEADER_INCLUDED
#define CACHE_HEADER_INCLUDED

#include <list>
#include <unordered_map>
#include <iterator>
#include <iostream>

const size_t MIN_SIZE = 8;

template <typename PageDataT, typename KeyT = int>
class Cache
{
private:
    enum Lists
    {
        T1_,
        T2_,
        B1_,
        B2_,
        NOT_IN_LISTS_
    };

// types
    using ListT  = typename std::list <PageDataT>;
    using ListIt = typename std::list <PageDataT>::iterator;
    struct MapT {
        Lists list_id = NOT_IN_LISTS_;
        ListIt value = (ListIt) nullptr;
    };
    using MapIt  = typename std::unordered_map <KeyT, MapT>::iterator;

// class fields
    std::unordered_map <KeyT, MapT> hash_table;
    ListT T1, T2, B1, B2;

    size_t cache_size;
    int p;

//------------------------------------------------------------------------------------------------------------

// functions

public:
    Cache(size_t size = MIN_SIZE): cache_size((size + 1)/2), p(0) {};
    ~Cache() {};
// primary functions 
public:
    bool RequestPage(const KeyT & page_number);
    void InsertPage(const KeyT& page_number);
    void MovePage(MapIt& page);
// instrumental functions
private:
    void MoveToOtherList(MapIt & page, ListT& list_from, ListT& list_to, const int & list_number);
    void InsertToList(const KeyT & page_number, const int & list_number, ListT& list_to);
    void MoveFromEnd(ListT& list_from, ListT& list_to, const int & list_number);
    void DeletePage(const MapIt & page, const int & list_number);
    void Replace_p(const int & list_number);
// information functions
public:
    void PrintList(const ListT& list, const std::string& list_name) const;
    void PrintInfo() const;
};

#endif