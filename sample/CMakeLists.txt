foreach (sample game editor make)
  add_library(sample_${sample} SHARED ${sample}.cpp)
  target_link_libraries(sample_${sample} PRIVATE blcore_dll blcore_settings)

  install(TARGETS sample_${sample} RUNTIME DESTINATION blcore)
endforeach ()
