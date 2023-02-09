//
//  utilities.hpp
//  project 5
//
//  Created by Isabelle Hales on 11/9/22.
//  Copyright © 2022 CS31. All rights reserved.
//

// utilities.h

const int MINWORDLEN = 4;
const int MAXWORDLEN = 6;

int getWords(char words[][MAXWORDLEN+1], int maxWords, const char wordfilename[]);
int randInt(int min, int max);
