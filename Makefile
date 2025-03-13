# Variáveis
CXX = g++
CXXFLAGS = -std=c++20
LDFLAGS = -ltbb
SRC_DIR = src/stl-parallel
SRC = $(wildcard $(SRC_DIR)/*.cpp)
BUILD_DIR = build
TARGET = $(BUILD_DIR)/reduce.out

# Regra padrão: compilar e executar
reduce: $(TARGET)
	@echo "reduce.out compiled"

vector: $(BUILD_DIR)/vector.out	
	@echo "vector compiled"

reference: src/pointer_references/reference.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/reference.out $(LDFLAGS)


string-view: src/string/string-view.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/string-view.out $(LDFLAGS)
	./$(BUILD_DIR)/string-view.out

raw-pointer: src/pointer_references/raw-pointer.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/raw-pointer.out $(LDFLAGS)
	./$(BUILD_DIR)/raw-pointer.out

smart-pointer: src/pointer_references/smart-pointer.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/smart-pointer.out $(LDFLAGS)
	./$(BUILD_DIR)/smart-pointer.out

constructor: src/pointer_references/constructor.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/constructor.out $(LDFLAGS)
	./$(BUILD_DIR)/constructor.out

constructor-example: src/pointer_references/constructor-example.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) -std=c++14 -fno-elide-constructors $^ -o $(BUILD_DIR)/constructor-example.out $(LDFLAGS)
	./$(BUILD_DIR)/constructor-example.out
	# $(CXX) -std=c++14 $^ -o $(BUILD_DIR)/constructor-example.out $(LDFLAGS)
	# ./$(BUILD_DIR)/constructor-example.out

atomic: src/multithread/atomic.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/atomic.out $(LDFLAGS)
	./$(BUILD_DIR)/atomic.out
	
mutex: src/multithread/mutex.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/mutex.out $(LDFLAGS)
	./$(BUILD_DIR)/mutex.out
	
latch-barrier-semaphore: src/multithread/latch-barrier-semaphore.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/latch-barrier-semaphore.out $(LDFLAGS)
	./$(BUILD_DIR)/latch-barrier-semaphore.out

future: src/multithread/future.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/future.out $(LDFLAGS)
	./$(BUILD_DIR)/future.out

thread-pools: src/multithread/thread-pools.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/thread-pools.out $(LDFLAGS)
	./$(BUILD_DIR)/thread-pools.out

boost-compute: src/multithread/boost-compute.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -I/usr/local/include/compute -o $(BUILD_DIR)/boost-compute.out $(LDFLAGS) -lOpenCL
	./$(BUILD_DIR)/boost-compute.out

views: src/ranges/views.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/views.out $(LDFLAGS)
	./$(BUILD_DIR)/views.out

condition: src/multithread/condition.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/condition.out $(LDFLAGS)
	./$(BUILD_DIR)/condition.out
	
$(BUILD_DIR)/vector.out: src/data-structure/vector.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	

# Regra de compilação
$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regra de limpeza
clean:
	@rm -rf $(BUILD_DIR)
