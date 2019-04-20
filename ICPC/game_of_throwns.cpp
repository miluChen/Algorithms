#include <vector>

// assume the undo is never beyond the start of the game
int game_of_throwns(int circle, std::vector<int> &commands, std::vector<bool> &undos) {
	// store all positions, so that undo is fast => time vs space tradeoff
	std::vector<int> positions(1, 0);

	int idx = 0;
	for (int i=0; i<commands.size(); i++) {
		if (undos[i])
			idx -= commands[i];
		else {
			int pos = (positions[idx] + commands[i]) % circle;
			pos = pos < 0 ? pos + circle : pos;
			positions[++idx] = pos;
		}
	}

	return positions[idx];
}
