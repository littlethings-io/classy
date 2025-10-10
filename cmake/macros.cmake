# ############################# MACROS ####################################
macro(SUBDIRLIST result curdir) # get all modules from this current list dir
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")

    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()

    set(${result} ${dirlist})
endmacro()

# macro for logging in this style to fit with the run.py style.
macro(LOGTHIS input)
    message("[CMAKE]   - ${input} -")
endmacro()