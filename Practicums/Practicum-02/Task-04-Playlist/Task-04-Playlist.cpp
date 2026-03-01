#include <iostream>

namespace Constants {
	const size_t MAX_TITLE_LENGTH = 100;
	const size_t MAX_NAME_LENGTH = 100;
	const size_t MAX_SONGS_COUNT = 64;
}

enum class Genre {
	Rock,
	Pop,
	ThrashMetal,
	KPop,
	Chalga
};

struct Song {
	char title[Constants::MAX_TITLE_LENGTH + 1] = "";
	char singer[Constants::MAX_NAME_LENGTH + 1] = "";
	Genre genre;
	double rating;
	size_t streamsCount = 0;

private:
	const char* genreToString(const Genre& genre) {
		switch (genre) {
		case Genre::Rock: return "Rock";
		case Genre::Pop: return "Pop";
		case Genre::ThrashMetal: return "Thrash Metal";
		case Genre::KPop: return "K-pop";
		case Genre::Chalga: return "Chalga";
		default: return "Unknown";
		}
	}

public:
	void printSong() {
		std::cout << "Title: " << title
				  << ", Singer: " << singer
				  << ", Genre: " << genreToString(genre)
				  << ", Rating: " << rating
				  << ", Streams: " << streamsCount
				  << std::endl;
	}
};

struct Playlist {
	Song songs[Constants::MAX_SONGS_COUNT];
	size_t songsCount = 0;

	void addSong(const Song& song) {
		if (songsCount >= Constants::MAX_SONGS_COUNT) {
			std::cout << "The playlist is full. Could not add the song." << std::endl;
			return;
		}

		songs[songsCount++] = song;
		std::cout << "Song added successfully." << std::endl;
	}

	Song* findSong(bool (*predicate)(const Song&)) {
		for (size_t i = 0; i < songsCount; i++) {
			if (predicate(songs[i])) {
				return &songs[i];
			}
		}

		return nullptr;
	}

	void sortSongs(bool(*predicate)(const Song&, const Song&)) {
		for (size_t i = 0; i < songsCount - 1; i++) {
			size_t minIndex = i;

			for (size_t j = i + 1; j < songsCount; j++) {
				if (predicate(songs[j], songs[minIndex])) {
					minIndex = j;
				}
			}

			if (minIndex != i) {
				Song temp = songs[i];
				songs[i] = songs[minIndex];
				songs[minIndex] = temp;
			}
		}
	}

	void printSongs() {
		for (size_t i = 0; i < songsCount; i++) {
			songs[i].printSong();
		}
	}
};

int main() {
	Playlist playlist{};

	Song song1 = { "Title1", "Singer1", Genre::Pop, 6.4, 13431 };
	Song song2 = { "Title2", "Singer2", Genre::Chalga, 8.8, 10243 };
	Song song3 = { "Title3", "Singer3", Genre::Rock, 7.3, 5 };

	playlist.addSong(song1);
	playlist.addSong(song2);
	playlist.addSong(song3);

	Song* popSong = playlist.findSong([](const Song& song) { return song.genre == Genre::Pop; });

	if (popSong) {
		popSong->printSong();
	}
	else {
		std::cout << "No pop song found!" << std::endl;
	}

	playlist.sortSongs([](const Song& s1, const Song& s2) {return s1.rating > s2.rating; });
	playlist.printSongs();
}