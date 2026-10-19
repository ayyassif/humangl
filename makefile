NAME := humangl

CXX := c++
CC  := cc

CXXFLAGS := -O2 -std=c++17 -fPIE # -Wall -Wextra
CFLAGS   := -O2 -fPIE

CPPFLAGS := $(addprefix -I,$(shell find src -type d)) \
            -Iexternal/glad/include \
            -Iexternal/imgui \
            -Iexternal/imgui/backends

LDFLAGS :=
LDLIBS  := -lglfw -lGL -ldl -pthread

SRC_DIR   := src
BUILD_DIR := build
IMGUI_DIR := external/imgui
GLAD_DIR  := external/glad

IMGUI_REPO := https://github.com/ocornut/imgui.git

IMGUI_SRCS := $(IMGUI_DIR)/imgui.cpp \
              $(IMGUI_DIR)/imgui_draw.cpp \
              $(IMGUI_DIR)/imgui_tables.cpp \
              $(IMGUI_DIR)/imgui_widgets.cpp \
              $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
              $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp') \
        $(IMGUI_SRCS)

OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
OBJS += $(BUILD_DIR)/$(GLAD_DIR)/src/glad.o

DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

# Download/generate GLAD if missing.
$(GLAD_DIR)/src/glad.c: | glad

glad:
	@if [ ! -f $(GLAD_DIR)/include/glad/glad.h ] || \
	    [ ! -f $(GLAD_DIR)/include/KHR/khrplatform.h ] || \
	    [ ! -f $(GLAD_DIR)/src/glad.c ]; then \
		python3 -m pip install -q glad==0.1.36 && \
		python3 -m glad --quiet --generator=c --out-path=$(GLAD_DIR) \
		    --profile=core --api=gl=4.0 --spec=gl --extensions=""; \
	fi

# Clone Dear ImGui if its source files are missing.
imgui:
	@if [ ! -f $(IMGUI_DIR)/imgui.cpp ] || \
	    [ ! -f $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp ] || \
	    [ ! -f $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp ]; then \
		mkdir -p external && \
		git clone --depth 1 $(IMGUI_REPO) $(IMGUI_DIR); \
	fi

# Ensure dependencies exist before compiling.
$(OBJS): | imgui glad

# Compile project and ImGui C++ sources.
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Compile generated GLAD C source.
$(BUILD_DIR)/$(GLAD_DIR)/src/glad.o: $(GLAD_DIR)/src/glad.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re glad imgui