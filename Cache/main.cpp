#include "includes/cache-impl.h"

bool start_tests();
int testing(FILE* file_test);
bool test1();
bool test2();
bool test3();
bool test4();
bool test5();
bool test6();
bool test7();
bool test8();
bool test9();
bool test10();

enum Streams
{
    stdin_,
    filein_
};
const Streams stream = stdin_;


int main(int argc, const char** argv)
{
    size_t size = 0, page_amount = 0;
    int hits = 0;

    #ifdef TESTING
    bool tests_passed = start_tests();
	if (tests_passed) 
		std::cout << "All the tests have been successfully passed" << std::endl;
	else
		std::cout << "Some tests have failed" << std::endl;
    #endif

    if (stream == stdin_)
    {
        std::cin >> size;
        Cache<int> cache{size};

        std::cin >> page_amount;
        for(size_t i = 0; i < page_amount; i++)
        {
            int page = 0;
            std::cin >> page;
            hits += cache.RequestPage(page);
        }
    }

    if (stream == filein_)
    {
        FILE* file_test = fopen(argv[1], "rt");
        if (!file_test)
        {
            printf("Error: can't open file.\n");
            return 0;
        }

        fscanf(file_test, "%lu", &size);
        fscanf(file_test, "%lu\n", &page_amount);

        Cache<int> cache{size};
        
        for(size_t i = 0; i < page_amount; i++)
        {
            int page = 0;
            fscanf(file_test, "%d\n", &page);
            hits += cache.RequestPage(page);
        }
    }
    
    std::cout << "hits in cache = " << hits << std::endl;

    return 0;
}

// functional testing

bool start_tests() 
{
    bool result = true;
    
    result = result && test1();
    result = result && test2();
    result = result && test3();
    result = result && test4();
    result = result && test5();
    result = result && test6();
    result = result && test7();
    result = result && test8();
    result = result && test9();
    result = result && test10();

    return result;
}

int testing(FILE* file_test)
{
    size_t size = 0, page_amount = 0;
    int hits = 0;

    fscanf(file_test, "%lu", &size);
    fscanf(file_test, "%lu\n", &page_amount);

    Cache<int> cache{size};
    
    for(size_t i = 0; i < page_amount; i++)
    {
        int page = 0;
        fscanf(file_test, "%d\n", &page);
        hits += cache.RequestPage(page);
    }

    return hits;
}

bool test1()
{
    FILE* file_test = fopen("tests/tasks/1.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 1.task.\n");
        return false;
    }

    if (testing(file_test) != 1050)
    {
        std::cout << "Test 1 has failed" << std::endl;
        return false;
    }

    return true;
}


bool test2()
{
    FILE* file_test = fopen("tests/tasks/2.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 2.task.\n");
        return false;
    }

    if (testing(file_test) != 1924)
    {
        std::cout << "Test 2 has failed" << std::endl;
        return false;
    }

    return true;
}

bool test3()
{
    FILE* file_test = fopen("tests/tasks/3.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 3.task.\n");
        return false;
    }

    if (testing(file_test) != 1854)
    {
        std::cout << "Test 3 has failed" << std::endl;
        return false;
    }

    return true;
}

bool test4()
{
    FILE* file_test = fopen("tests/tasks/4.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 4.task.\n");
        return false;
    }

    if (testing(file_test) != 1947)
    {
        std::cout << "Test 4 has failed" << std::endl;
        return false;
    }

    return true;
}

bool test5()
{
    FILE* file_test = fopen("tests/tasks/5.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 5.task.\n");
        return false;
    }

    if (testing(file_test) != 1955)
    {
        std::cout << "Test 5 has failed" << std::endl;
        return false;
    }

    return true;
}

bool test6()
{
    FILE* file_test = fopen("tests/tasks/6.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 6.task.\n");
        return false;
    }

    if (testing(file_test) != 1944)
    {
        std::cout << "Test 6 has failed" << std::endl;
        return false;
    }

    return true;
}

bool test7()
{
    FILE* file_test = fopen("tests/tasks/7.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 7.task.\n");
        return false;
    }

    if (testing(file_test) != 1960)
    {
        std::cout << "Test 7 has failed" << std::endl;
        return false;
    }

    return true;
}

bool test8()
{
    FILE* file_test = fopen("tests/tasks/8.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 8.task.\n");
        return false;
    }

    if (testing(file_test) != 1869)
    {
        std::cout << "Test 8 has failed" << std::endl;
        return false;
    }

    return true;
}

bool test9()
{
    FILE* file_test = fopen("tests/tasks/9.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 9.task.\n");
        return false;
    }

    if (testing(file_test) != 1957)
    {
        std::cout << "Test 9 has failed" << std::endl;
        return false;
    }

    return true;
}

bool test10()
{
    FILE* file_test = fopen("tests/tasks/10.task", "rt");
    if (!file_test)
    {
        printf("Error: can't open file 10.task.\n");
        return false;
    }

    if (testing(file_test) != 1950)
    {
        std::cout << "Test 10 has failed" << std::endl;
        return false;
    }

    return true;
}