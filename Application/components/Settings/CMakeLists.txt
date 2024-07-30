idf_component_register(SRCS 
			"settingsIni.cpp"
			"ConvertUTF.c"  
                    INCLUDE_DIRS 
		    "."
		    ".." 
                    REQUIRES nvs_flash)
