add_executable(test_complex test_complex.cpp
        doctest.h)
target_link_libraries(test_complex complex)

add_executable(test_rational test_rational.cpp)
target_link_libraries(test_rational rational)

add_executable(test_dynarr test_dynarr.cpp)
target_link_libraries(test_dynarr dynarr)

