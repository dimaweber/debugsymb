set(DEBUG_SYMBOL_SUFFIX ds)
set(SYMBOLS_BINARY_PATH ${CMAKE_BINARY_DIR}/symbols)
file(MAKE_DIRECTORY ${SYMBOLS_BINARY_PATH})

function(create_ds target)
    set(TARGET_DS ${SYMBOLS_BINARY_PATH}/$<TARGET_FILE_NAME:${target}>.${DEBUG_SYMBOL_SUFFIX})

    add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${target}> ${TARGET_DS}
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${target}>
            COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=${TARGET_DS} $<TARGET_FILE:${target}>
    )
endfunction()
install(DIRECTORY ${SYMBOLS_BINARY_PATH} TYPE INFO)
