foreach (sample game editor make)
  add_library(sample_${sample} SHARED ${sample}.cpp)
  target_link_libraries(sample_${sample} PRIVATE blcore)

  set_target_properties(sample_${sample}
      PROPERTIES
      CXX_STANDARD 23
      CXX_STANDARD_REQUIRED ON
      CXX_EXTENSIONS OFF
  )

  if (MSVC)
    target_compile_options(sample_${sample} PRIVATE /W4 /EHsc /utf-8)
  endif ()

  install(TARGETS sample_${sample} RUNTIME DESTINATION blcore)
endforeach ()
