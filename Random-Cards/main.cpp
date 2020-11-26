#include <iostream>
#include <vector>
#include <time.h>
#include <cstring>
#include <numeric>	//for iota
#include <algorithm> //for shuffle

const unsigned total_plays = 1e6;
const unsigned players = 2;
const unsigned no_cards = 52;
const unsigned no_f_cards = 1;
const unsigned no_suits = 4;

const unsigned faces = no_cards / no_suits;

unsigned wins[players]{};
unsigned tf_cards[no_f_cards * no_suits];

std::vector<unsigned> cards;

unsigned cards_chosen[no_f_cards];
unsigned turn_counter = 0;
bool not_break = true;

unsigned indices[no_f_cards * no_suits];

unsigned sum;

bool valid;

int main() {
	//setup
	srand(time(NULL));
	cards.resize(no_cards);
	std::iota(cards.begin(), cards.end(), 0);

	std::random_shuffle(cards.begin(), cards.end());

	for (size_t i = 0; i < no_f_cards * no_suits; i++) {
		tf_cards[i] = cards[i];
	}


	for (unsigned k = 0; k < total_plays; k++) {
		while (not_break) {
			//select a card

			for (size_t i = 0; i < no_f_cards; i++) {
				indices[i] = rand() % (no_cards - i);
				cards_chosen[i] = cards[indices[i]];
				cards.erase(cards.begin() + indices[i]);
			}
			//std::random_shuffle(cards.begin(), cards.end());

			//for (size_t i = 0; i < no_f_cards; i++) {
			//	cards_chosen[i] = cards[i];
			//}

			valid = true;
			for (size_t i = 0; i < no_f_cards; i++){
				for (size_t j = i + 1; j < no_f_cards; j++) {
					if ((cards_chosen[i] % faces) == (cards_chosen[j] % faces) ) {
						valid = false;
						goto outside;
					}
				}
			}
			outside:

			if (valid) {
				sum = 0;
				for (size_t j = 0; j < no_f_cards; j++) {
					for (size_t i = 0; i < no_f_cards * no_suits; i++) {
						if (cards_chosen[j] == tf_cards[i]){
							sum++;
						}
					}
				}

				if (sum == no_f_cards){
					wins[turn_counter % players]++;
					not_break = false;
				}

			}


			for (size_t i = 0; i < no_f_cards; i++) {
				cards.push_back(indices[i]);
			}

			turn_counter++;
			//std::cout << turn_counter << std::endl;
		}
		not_break = true;
		turn_counter = 0;


	}

	std::cout << "for " << no_f_cards << " favourable cards and " << total_plays << " total plays" << std::endl;
	for (int i = 0; i < players; i++) {
		std::cout << "player " << i << " won " << wins[i] << " times" << std::endl;
	}

	return 0;
}
