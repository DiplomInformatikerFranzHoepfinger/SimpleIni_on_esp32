idf_component_register(SRCS 
			"settingsIni.cpp"
                    INCLUDE_DIRS 
		    "."
		    ".." 
                    PRIV_REQUIRES nvs_flash SimpleIni )
