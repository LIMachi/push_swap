TARGET_CHECKER := false
TARGET_PUSH_SWAP := false

ifeq ($(filter checker, $(MAKECMDGOALS)), checker)
TARGET_CHECKER := true
endif

ifeq ($(filter push_swap, $(MAKECMDGOALS)), push_swap)
TARGET_PUSH_SWAP := true
endif

ifeq ($(TARGET_CHECKER), false)
ifeq ($(TARGET_PUSH_SWAP), false)
TARGET_CHECKER := true
TARGET_PUSH_SWAP := true
endif
endif

SUBMAKECMDGOALS := $(filter-out checker, $(filter-out push_swap, $(MAKECMDGOALS)))
ifeq ($(SUBMAKECMDGOALS), )
SUBMAKECMDGOALS := all
endif

ifeq ($(TARGET_CHECKER), true)
# $(warning $(shell $(MAKE) -C check $(SUBMAKECMDGOALS)))
$(info $(shell $(MAKE) -C checker_app $(SUBMAKECMDGOALS)))
endif

ifeq ($(TARGET_PUSH_SWAP), true)
$(info $(shell $(MAKE) -C push_swap_app $(SUBMAKECMDGOALS)))
endif

all:
	@[ 0 = 0 ]
$(MAKECMDGOALS):
	@[ 0 = 0 ]
