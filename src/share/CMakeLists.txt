add_library(
	spindulysShare INTERFACE
)

target_sources(spindulysShare INTERFACE
	FILE_SET HEADERS
	BASE_DIRS ./
	FILES ./spindulys.h spindulys/mathHelper.h
)
