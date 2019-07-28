function (find_headers path_to_search header_list)
    file (GLOB_RECURSE headers ${path_to_search}/*.h ${path_to_search}/*.hpp)

    list(TRANSFORM headers
        PREPEND
            "\""
    )

    list(TRANSFORM headers
        APPEND
            "\""
    )

    string(REPLACE ";" "," ${header_list} "${headers}")

    set (${header_list} ${headers} PARENT_SCOPE)
endfunction()
