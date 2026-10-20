NAME := humangl

CXX := c++
CC  := cc

CXXFLAGS := -O2 -std=c++17 -fPIE
CFLAGS   := -O2 -fPIE

SRC_DIR   := src
BUILD_DIR := build
IMGUI_DIR := external/imgui
GLAD_DIR  := external/glad

IMGUI_REPO := https://github.com/ocornut/imgui.git

# ---- Detect optional externals (evaluated at parse time) ----
HAVE_IMGUI := $(and $(wildcard $(IMGUI_DIR)/imgui.cpp),\
                    $(wildcard $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp),\
                    $(wildcard $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp))
HAVE_GLAD  := $(and $(wildcard $(GLAD_DIR)/include/glad/glad.h),\
                    $(wildcard $(GLAD_DIR)/include/KHR/khrplatform.h),\
                    $(wildcard $(GLAD_DIR)/src/glad.c))

CPPFLAGS := $(addprefix -I,$(shell find $(SRC_DIR) -type d))
LDLIBS   := -lglfw -lGL -ldl -pthread

PROJECT_SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
EXTRA_SRCS   :=
EXTRA_OBJS   :=

ifneq ($(HAVE_IMGUI),)
CPPFLAGS += -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -DHAVE_IMGUI
EXTRA_SRCS += $(IMGUI_DIR)/imgui.cpp \
              $(IMGUI_DIR)/imgui_draw.cpp \
              $(IMGUI_DIR)/imgui_tables.cpp \
              $(IMGUI_DIR)/imgui_widgets.cpp \
              $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
              $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
endif

ifneq ($(HAVE_GLAD),)
CPPFLAGS += -I$(GLAD_DIR)/include -DHAVE_GLAD
EXTRA_OBJS += $(BUILD_DIR)/$(GLAD_DIR)/src/glad.o
endif

OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(PROJECT_SRCS) $(EXTRA_SRCS)) $(EXTRA_OBJS)

.PHONY: all setup build clean fclean re glad imgui

all: setup
	@$(MAKE) --no-print-directory build

setup: imgui glad

build: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $^ $(LDLIBS) -o $@

# Best-effort fetch: never fails the build
imgui:
	@if [ ! -f $(IMGUI_DIR)/imgui.cpp ]; then \
		mkdir -p external && \
		git clone --depth 1 $(IMGUI_REPO) $(IMGUI_DIR) >/dev/null 2>&1 \
		|| echo "warning: could not fetch imgui, building without it"; \
	fi

glad:
	@if [ ! -f $(GLAD_DIR)/src/glad.c ]; then \
		( python3 -m pip install -q glad==0.1.36 && \
		  python3 -m glad --quiet --generator=c --out-path=$(GLAD_DIR) \
		      --profile=core --api=gl=4.0 --spec=gl --extensions="" ) >/dev/null 2>&1 \
		|| echo "warning: could not generate glad, building without it"; \
	fi

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/$(GLAD_DIR)/src/glad.o: $(GLAD_DIR)/src/glad.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(shell find $(BUILD_DIR) -name '*.d' 2>/dev/null)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all