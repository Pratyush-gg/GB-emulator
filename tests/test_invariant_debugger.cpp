#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

class DebuggerSecurityTest : public ::testing::TestWithParam<std::string> {};

TEST_P(DebuggerSecurityTest, BufferOverflowProtection) {
    // Invariant: The debugger must not crash or exhibit undefined behavior
    // when processing commands longer than internal buffer limits.
    // The process must remain stable and not segfault.
    
    std::string payload = GetParam();
    
    // Create a test program that calls the vulnerable debugger function
    std::string test_prog = R"(
#include <string>
#include <cstring>
extern void executeCommand(const std::string& command);
int main() {
    std::string cmd = ")" + payload + R"(";
    try {
        executeCommand(cmd);
    } catch (...) {
        return 1;
    }
    return 0;
}
)";
    
    // Write test program to temp file
    FILE* f = fopen("/tmp/test_debugger.cpp", "w");
    fprintf(f, "%s", test_prog.c_str());
    fclose(f);
    
    // Compile with the actual debugger.cpp
    int compile_result = system(
        "g++ -o /tmp/test_debugger /tmp/test_debugger.cpp src/debugger.cpp 2>/dev/null"
    );
    
    if (compile_result == 0) {
        // Run the test program with timeout
        pid_t pid = fork();
        if (pid == 0) {
            alarm(2);  // 2-second timeout
            execl("/tmp/test_debugger", "/tmp/test_debugger", nullptr);
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
            // Invariant: Process must not segfault (SIGSEGV = signal 11)
            EXPECT_FALSE(WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
                << "Buffer overflow detected with payload length: " << payload.length();
        }
    }
    
    system("rm -f /tmp/test_debugger /tmp/test_debugger.cpp");
}

INSTANTIATE_TEST_SUITE_P(
    AdversarialInputs,
    DebuggerSecurityTest,
    ::testing::Values(
        std::string(256, 'A'),           // Exact overflow: typical stack buffer
        std::string(1024, 'B'),          // Large overflow payload
        std::string(512, 'C'),           // Boundary case
        "help",                          // Valid input (baseline)
        std::string(100, 'D')            // Sub-buffer valid input
    )
);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}