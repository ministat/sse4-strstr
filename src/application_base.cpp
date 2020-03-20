class ApplicationBase {

protected:
    std::string file;
    std::vector<std::string> words;
    std::vector<std::string> lines;
public:
    class Error final {
    public:
        const std::string message;

    public:
        Error(const std::string& msg) : message(msg) {}
    };

public:
    void prepare(const std::string& file_name, const std::string& words_name) {

        load_text(file_name);
        load_words(words_name);
    }

    void prepare_multiple(const std::string& file_name, const std::string& words_name) {

        prepare(file_name, words_name);
	load_lines(file_name);
    }

private:
    void load_text(const std::string& path) {

        FILE* f = fopen(path.c_str(), "rt");
        if (f == nullptr) {
            throw_errno(path);
        }

        fseek(f, -1, SEEK_END);
        const auto size = ftell(f);

        rewind(f);

        char* buffer = new char[size];
        if (fread(buffer, size, 1, f) != 1) {
	}
        buffer[size] = 0;
        fclose(f);

        file = buffer;

        delete[] buffer;
    }

    void load_lines(const std::string& path) {

        char buffer[655350];

        FILE* f = fopen(path.c_str(), "rt");
        if (f == nullptr) {
            throw_errno(path);
        }

        while (fgets(buffer, sizeof(buffer), f) != NULL) {
            const auto len = strlen(buffer);
            if (buffer[len - 1] == '\n') {
                buffer[len - 1] = 0;
                if (len == 1) // skip empty strings
                    continue;
            }

            lines.push_back(buffer);
	}

        fclose(f);
    }

    void load_words(const std::string& path) {

        char buffer[1024];

        FILE* f = fopen(path.c_str(), "rt");
        if (f == nullptr) {
            throw_errno(path);
        }

        while (fgets(buffer, sizeof(buffer), f) != NULL) {
            const auto len = strlen(buffer);
            if (buffer[len - 1] == '\n') {
                buffer[len - 1] = 0;
                if (len == 1) // skip empty strings
                    continue;
            }

            words.push_back(buffer);
	}

        fclose(f);
    }


    void throw_errno(const std::string& prefix) {

        const std::string msg = prefix + ": " + std::string(strerror(errno));
        throw Error(msg);
    }
};

