cmake_minimum_required(VERSION 3.23)

project(tikee)

add_executable(tikee_app)
target_sources(tikee_app
	PRIVATE
		main.cpp
)
