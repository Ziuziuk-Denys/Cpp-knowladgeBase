#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Song {
    public:
        std::string title;
        std::string artist;
        double duration;

    Song(std::string t, std::string a, double d) {
        title = t;
        artist = a;
        duration = d;
    }

    void display() {
        std::cout << artist << " - " << title << " " << duration << "min" << std::endl;
    }

};

int main() {
    std::vector<Song*> tasks;

    std::string title = "";
    std::string  artist = "";
    double duration = 0.0;

    while (true) {
        std::cout << "Enter title of the song or (exit): ";
        std::getline(std::cin, title);
        if (title == "exit") break;

        std::cout << "Enter artist name: ";
        std::cin >> artist;

        std::cout << "Enter duration: ";
        std::cin >> duration;

        tasks.push_back(new Song(title, artist, duration));

        std::cout << "Now playing: " << std::endl;

        for (size_t i = 0; i < tasks.size(); i++) {
            tasks[i]->display();
        }
    }

    std::ofstream outFile("playlist.txt");

    if (outFile.is_open()) {

        for (Song* s : tasks) {
            outFile << s->artist << "|" << s->title << "|" << s->duration << std::endl;
        }
        outFile.close();

        std::cout << "Playlist saved to playlist.txt!" << std::endl;
    } else {
        std::cerr << "Error: Could not save file!" << std::endl;
    }

    for (Song* song : tasks) {
        delete song;
    }
}
