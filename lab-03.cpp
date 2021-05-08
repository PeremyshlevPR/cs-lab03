#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<double> input_numbers(size_t count)
{
    cerr << "Enter numbers: ";
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }
}

vector <size_t> make_histogram(const vector<double>& numbers, size_t bin_count)
{
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> result(bin_count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        result[bin]++;
    }
    return result;
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg_rect(double left, double baseline, size_t width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x ='" << left << "' y ='" << baseline << "' width ='" << width << "' height ='" << height << "' stroke ='" << stroke << "' fill ='" << fill << "' />\n";
}

void show_histogram_svg(const vector<size_t>& bins) 
{
    const auto IMAGE_WIDTH = 400;
    const auto MAX_WIDTH = 350;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const double BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    string red = "red";
    string green = "green";

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = (max_count * BLOCK_WIDTH) > MAX_WIDTH;

    for (size_t bin : bins) 
    {
        const double bin_width = BLOCK_WIDTH * bin;

        size_t width = bin_width;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_WIDTH / (max_count * BLOCK_WIDTH);
            width = (bin_width * scaling_factor);
        }

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, width, BIN_HEIGHT, red, green);
        top += BIN_HEIGHT;
    }
    svg_end();
}




void show_histogram_text(vector<double> bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }
}

int main() 
{
    // Ввод данных
    size_t count;
    cerr << "Enter number count: ";
    cin >> count;

const auto numbers = input_numbers(count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    // Обработка данных
    // поиск min и max
    
    const auto bins = make_histogram(numbers, bin_count);
    
    // Вывод данных
    show_histogram_svg(bins);

    return 0;
}
