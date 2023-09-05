#include <iostream>

// Using enum in local scopes

enum class Color {
    Red, Green, Blue,
};

int main() {
    Color color = Color::Blue;

    switch (color) {
        // Local scope 에 using enum 을 사용해서 코드양을 줄일 수 있다.
        using enum Color;
        case Blue:
            break;
        case Red:
            break;
        case Green:
            break;
    }
}