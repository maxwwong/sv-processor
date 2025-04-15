# -------- CONFIG --------
TOP_MODULE     = alu
SV_SRC         = src/alu.sv
CPP_TESTBENCH  = sim/alu_tb.cpp
INCLUDE_DIRS   = -Iinclude
BUILD_DIR      = obj_dir
EXE_NAME       = $(BUILD_DIR)/V$(TOP_MODULE)

# -------- DEFAULT TARGET --------
all: run

# -------- VERILATE + COMPILE --------
$(EXE_NAME): $(SV_SRC) $(CPP_TESTBENCH)
	verilator -Wall -cc $(SV_SRC) --exe $(CPP_TESTBENCH) $(INCLUDE_DIRS)
	make -C $(BUILD_DIR) -f V$(TOP_MODULE).mk

# -------- RUN SIM --------
run: $(EXE_NAME)
	./$(EXE_NAME)

# -------- CLEAN --------
clean:
	rm -rf $(BUILD_DIR) logs
