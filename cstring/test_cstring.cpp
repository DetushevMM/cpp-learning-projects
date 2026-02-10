#include <iostream>
#include <cassert>
#include "cstring.hpp"

int main() {
    char buf[50];

    // 1. Strlen
    assert(Strlen("hello") == 5);
    assert(Strlen("") == 0);

    // 2. Strcmp
    assert(Strcmp("abc", "abc") == 0);
    assert(Strcmp("abc", "abd") < 0);
    assert(Strcmp("abd", "abc") > 0);
    assert(Strcmp("ab", "abc") < 0);
    assert(Strcmp("abc", "ab") > 0);

    // 3. Strncmp
    assert(Strncmp("abcdef", "abcxyz", 3) == 0);
    assert(Strncmp("abcdef", "abcxyz", 4) < 0);
    assert(Strncmp("abc", "abz", 2) == 0);
    assert(Strncmp("abc", "abz", 3) < 0);

    // 4. Strchr
    assert(Strchr("hello", 'e') == &("hello"[1]));
    assert(Strchr("hello", 'x') == nullptr);
    assert(Strchr("hello", '\0') == &("hello"[5]));

    // 5. Strrchr
    assert(Strrchr("hello", 'l') == &("hello"[3]));
    assert(Strrchr("hello", 'x') == nullptr);
    assert(Strrchr("hello", '\0') == &("hello"[5]));

    // 6. Strspn
    assert(Strspn("abcde", "abc") == 3);
    assert(Strspn("abcd", "xyz") == 0);

    // 7. Strcspn
    assert(Strcspn("abcdef", "xyz") == 6);
    assert(Strcspn("abcdef", "d") == 3);

    // 8. Strpbrk
    assert(Strpbrk("abcdef", "xyz") == nullptr);
    assert(Strpbrk("abcdef", "cdx") == &("abcdef"[2]));

    // 9. Strstr
    assert(Strstr("hello world", "world") == &("hello world"[6]));
    assert(Strstr("hello world", "xyz") == nullptr);
    assert(Strstr("hello", "") == &("hello"[0]));

    // 10. Strcpy
    Strcpy(buf, "test");
    assert(Strcmp(buf, "test") == 0);

    // 11. Strncpy
    Strncpy(buf, "abc", 5);
    assert(buf[0] == 'a' && buf[1] == 'b' && buf[2] == 'c' &&
           buf[3] == '\0' && buf[4] == '\0');

    Strncpy(buf, "abcdef", 3);
    assert(buf[0] == 'a' && buf[1] == 'b' && buf[2] == 'c');

    // 12. Strcat
    Strcpy(buf, "Hello");
    Strcat(buf, " World");
    assert(Strcmp(buf, "Hello World") == 0);

    // 13. Strncat
    Strcpy(buf, "Foo");
    Strncat(buf, "BarBaz", 3);
    assert(Strcmp(buf, "FooBar") == 0);

    Strcpy(buf, "Foo");
    Strncat(buf, "Hi", 5);
    assert(Strcmp(buf, "FooHi") == 0);

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
