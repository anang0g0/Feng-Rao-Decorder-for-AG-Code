#include <stdio.h>


static int g[24][288]={
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,0,1,1,2,2,4,4,16,16,32,32,128,128,29,29,116,116,232,232,19,19,38,38,76,76,152,152,90,90,
	180,180,117,117,234,234,24,24,96,96,192,192,157,157,78,78,148,148,106,106,181,181,119,119,
	238,238,193,193,140,140,10,10,40,40,93,93,210,210,185,185,111,111,222,222,95,95,190,190,
	153,153,47,47,15,15,30,30,60,60,240,240,253,253,231,231,187,187,107,107,214,214,177,177,
	127,127,254,254,225,225,223,223,182,182,226,226,175,175,67,67,34,34,68,68,136,136,26,26,
	52,52,129,129,237,237,199,199,147,147,59,59,236,236,151,151,51,51,204,204,133,133,46,46,
	92,92,109,109,169,169,79,79,158,158,33,33,84,84,164,164,85,85,73,73,146,146,57,57,213,213,
	183,183,230,230,191,191,145,145,63,63,126,126,252,252,229,229,215,215,179,179,123,123,241,
	241,255,255,227,227,171,171,75,75,150,150,110,110,220,220,174,174,65,65,25,25,50,50,100,
	100,200,200,14,14,112,112,221,221,83,83,89,89,178,178,121,121,242,242,239,239,155,155,69,
	69,9,9,18,18,36,36,144,144,243,243,251,251,235,235,203,203,11,11,22,22,44,44,88,88,250,
	250,233,233,131,131,27,27,108,108,216,216,71,71,142,142},
{1,1,0,1,1,4,4,16,16,29,29,116,116,19,19,76,76,180,180,234,234,24,24,96,96,157,157,78,78,148,
	148,106,106,181,181,238,238,93,93,185,185,222,222,95,95,153,153,30,30,253,253,107,107,177,
	177,254,254,223,223,67,67,68,68,52,52,129,129,199,199,59,59,236,236,151,151,133,133,46,46,
	79,79,33,33,85,85,73,73,57,57,183,183,230,230,191,191,63,63,252,252,215,215,123,123,241,
	241,227,227,171,171,150,150,110,110,174,174,50,50,200,200,112,112,221,221,83,83,89,89,121,
	121,18,18,251,251,203,203,11,11,44,44,250,250,27,27,108,108,142,142,2,2,32,32,128,128,232,
	232,38,38,152,152,90,90,117,117,192,192,119,119,193,193,140,140,10,10,40,40,210,210,111,
	111,190,190,47,47,15,15,60,60,240,240,231,231,187,187,214,214,127,127,225,225,182,182,226,
	226,175,175,34,34,136,136,26,26,237,237,147,147,51,51,204,204,92,92,109,109,169,169,158,
	158,84,84,164,164,146,146,213,213,145,145,126,126,229,229,179,179,255,255,75,75,220,220,
	65,65,25,25,100,100,14,14,178,178,242,242,239,239,155,155,69,69,9,9,36,36,144,144,243,243,
	235,235,22,22,88,88,233,233,131,131,216,216,71,71},
{1,1,0,1,1,8,8,64,64,205,205,38,38,117,117,143,143,96,96,39,39,181,181,193,193,70,70,10,10,
	186,186,185,185,161,161,97,97,107,107,223,223,182,182,217,217,68,68,62,62,59,59,102,102,
	23,23,184,184,169,169,41,41,146,146,115,115,252,252,219,219,150,150,196,196,110,110,130,
	130,100,100,221,221,166,166,36,36,61,61,245,245,139,139,44,44,125,125,54,54,173,173,1,1,
	8,8,64,64,58,58,205,205,38,38,143,143,96,96,37,37,53,53,70,70,10,10,80,80,185,185,161,161,
	231,231,217,217,134,134,68,68,26,26,206,206,237,237,59,59,102,102,23,23,169,169,33,33,168,
	168,85,85,146,146,228,228,115,115,241,241,130,130,100,100,56,56,221,221,166,166,195,195,
	86,86,36,36,245,245,44,44,125,125,207,207,54,54,173,173,1,1,8,8,64,64,205,205,38,38,45,45,
	143,143,12,12,96,96,70,70,10,10,185,185,161,161,47,47,101,101,15,15,120,120,127,127,217,
	217,68,68,208,208,59,59,197,197,102,102,23,23,169,169,21,21,146,146,115,115,191,191,145,
	145,179,179,87,87,130,130,100,100,7,7,221,221,166,166,89,89,242,242,138,138,36,36,245,
	245,251,251,44,44,125,125,54,54,173,173},
{1,1,0,1,1,16,16,29,29,76,76,180,180,24,24,157,157,106,106,238,238,93,93,185,185,95,95,153,
	153,30,30,253,253,107,107,254,254,129,129,59,59,151,151,133,133,79,79,73,73,230,230,252,
	252,123,123,227,227,150,150,200,200,221,221,121,121,18,18,203,203,44,44,250,250,27,27,2,
	2,32,32,152,152,117,117,193,193,140,140,40,40,111,111,190,190,47,47,60,60,231,231,214,
	214,225,225,182,182,175,175,34,34,26,26,237,237,51,51,109,109,158,158,164,164,146,146,
	213,213,145,145,229,229,25,25,242,242,155,155,69,69,36,36,243,243,88,88,233,233,71,71,4,
	4,116,116,19,19,234,234,96,96,78,78,148,148,181,181,222,222,177,177,223,223,67,67,68,68,
	52,52,199,199,236,236,46,46,33,33,85,85,57,57,183,183,191,191,63,63,215,215,241,241,171,
	171,110,110,174,174,50,50,112,112,83,83,89,89,251,251,11,11,108,108,142,142,128,128,232,
	232,38,38,90,90,192,192,119,119,10,10,210,210,15,15,240,240,187,187,127,127,226,226,136,
	136,147,147,204,204,92,92,169,169,84,84,126,126,179,179,255,255,75,75,220,220,65,65,100,
	100,14,14,178,178,239,239,9,9,144,144,235,235,22,22,131,131,216,216},
{1,1,0,1,1,32,32,116,116,180,180,3,3,156,156,106,106,5,5,160,160,94,94,15,15,253,253,214,214,
	226,226,17,17,26,26,103,103,132,132,85,85,114,114,230,230,215,215,174,174,28,28,89,89,
	239,239,172,172,36,36,233,233,1,1,116,116,3,3,106,106,193,193,5,5,160,160,190,190,94,94,
	214,214,223,223,59,59,51,51,46,46,132,132,77,77,85,85,230,230,145,145,215,215,255,255,
	150,150,55,55,174,174,100,100,89,89,172,172,244,244,235,235,108,108,1,1,32,32,38,38,180,
	180,5,5,15,15,253,253,214,214,223,223,17,17,103,103,124,124,51,51,46,46,132,132,77,77,
	114,114,145,145,215,215,255,255,150,150,167,167,235,235,44,44,108,108,1,1,32,32,180,180,
	3,3,156,156,193,193,185,185,190,190,94,94,15,15,253,253,214,214,223,223,226,226,26,26,
	103,103,124,124,51,51,46,46,169,169,145,145,215,215,55,55,174,174,28,28,167,167,89,89,
	239,239,244,244,233,233,1,1,116,116,96,96,156,156,106,106,193,193,160,160,190,190,214,
	214,226,226,17,17,26,26,124,124,77,77,85,85,114,114,230,230,215,215,255,255,150,150,55,
	55,28,28,167,167,239,239,172,172,244,244,235,235,233,233,108,108},
{1,1,0,1,1,64,64,205,205,143,143,96,96,181,181,70,70,185,185,97,97,107,107,223,223,217,217,
	68,68,62,62,59,59,102,102,184,184,252,252,150,150,110,110,130,130,221,221,61,61,44,44,
	173,173,8,8,58,58,38,38,53,53,10,10,161,161,231,231,134,134,26,26,206,206,237,237,23,23,
	169,169,146,146,115,115,100,100,56,56,166,166,86,86,36,36,245,245,125,125,54,54,1,1,64,
	64,205,205,45,45,143,143,96,96,70,70,185,185,101,101,120,120,217,217,68,68,208,208,59,59,
	102,102,191,191,130,130,7,7,221,221,89,89,138,138,251,251,44,44,173,173,8,8,38,38,117,
	117,39,39,193,193,10,10,186,186,161,161,182,182,23,23,169,169,41,41,146,146,115,115,219,
	219,196,196,100,100,166,166,36,36,245,245,139,139,125,125,54,54,1,1,64,64,205,205,143,
	143,96,96,37,37,70,70,80,80,185,185,217,217,68,68,59,59,102,102,33,33,168,168,85,85,228,
	228,241,241,130,130,221,221,195,195,44,44,207,207,173,173,8,8,38,38,12,12,10,10,161,161,
	47,47,15,15,127,127,197,197,23,23,169,169,21,21,146,146,115,115,145,145,179,179,87,87,
	100,100,166,166,242,242,36,36,245,245,125,125,54,54},
{1,1,0,1,1,128,128,19,19,24,24,156,156,140,140,93,93,94,94,60,60,67,67,26,26,129,129,147,147,
	109,109,132,132,41,41,57,57,200,200,89,89,155,155,18,18,11,11,232,232,3,3,53,53,159,159,
	40,40,185,185,254,254,68,68,248,248,158,158,183,183,145,145,123,123,75,75,25,25,28,28,69,
	69,61,61,38,38,234,234,48,48,119,119,5,5,186,186,188,188,120,120,214,214,91,91,134,134,
	52,52,31,31,59,59,21,21,114,114,229,229,227,227,141,141,221,221,178,178,36,36,247,247,90,
	90,80,80,111,111,153,153,15,15,225,225,136,136,103,103,151,151,92,92,77,77,73,73,63,63,
	150,150,220,220,50,50,56,56,203,203,201,201,96,96,238,238,10,10,105,105,240,240,177,177,
	17,17,62,62,169,169,42,42,164,164,228,228,99,99,215,215,219,219,149,149,7,7,167,167,121,
	121,72,72,243,243,44,44,12,12,78,78,160,160,222,222,30,30,187,187,223,223,175,175,199,
	199,66,66,146,146,126,126,100,100,112,112,162,162,195,195,244,244,250,250,152,152,192,
	192,148,148,193,193,210,210,34,34,208,208,124,124,236,236,79,79,84,84,85,85,213,213,171,
	171,55,55,14,14,83,83,172,172,144,144,88,88,27,27},
{1,1,0,1,1,29,29,76,76,157,157,106,106,93,93,95,95,253,253,254,254,129,129,59,59,133,133,79,
	79,73,73,230,230,252,252,227,227,18,18,44,44,27,27,2,2,152,152,140,140,190,190,231,231,
	225,225,175,175,26,26,158,158,146,146,229,229,25,25,155,155,36,36,243,243,88,88,4,4,116,
	116,78,78,181,181,223,223,67,67,52,52,236,236,46,46,33,33,57,57,191,191,215,215,171,171,
	110,110,50,50,112,112,89,89,251,251,108,108,232,232,90,90,119,119,10,10,210,210,15,15,
	187,187,92,92,179,179,75,75,220,220,100,100,178,178,144,144,235,235,216,216,16,16,180,
	180,24,24,238,238,185,185,153,153,30,30,107,107,151,151,123,123,150,150,200,200,221,221,
	121,121,203,203,250,250,32,32,117,117,193,193,40,40,111,111,47,47,60,60,214,214,182,182,
	34,34,237,237,51,51,109,109,164,164,213,213,145,145,242,242,69,69,233,233,71,71,19,19,
	234,234,96,96,148,148,222,222,177,177,68,68,199,199,85,85,183,183,63,63,241,241,174,174,
	83,83,11,11,142,142,128,128,38,38,192,192,240,240,127,127,226,226,136,136,147,147,204,
	204,169,169,84,84,126,126,255,255,65,65,14,14,239,239,9,9,22,22,131,131},
{1,1,0,1,1,58,58,45,45,37,37,193,193,161,161,101,101,223,223,134,134,102,102,169,169,168,168,
	146,146,179,179,150,150,87,87,7,7,173,173,38,38,143,143,39,39,10,10,127,127,26,26,197,
	197,184,184,21,21,85,85,110,110,221,221,138,138,54,54,117,117,96,96,53,53,70,70,97,97,15,
	15,68,68,206,206,145,145,241,241,196,196,56,56,89,89,86,86,139,139,207,207,1,1,58,58,45,
	45,12,12,37,37,193,193,101,101,223,223,208,208,237,237,168,168,146,146,191,191,150,150,
	87,87,125,125,39,39,181,181,10,10,185,185,120,120,217,217,26,26,197,197,184,184,85,85,
	115,115,219,219,100,100,221,221,242,242,138,138,205,205,97,97,15,15,182,182,68,68,206,
	206,33,33,41,41,145,145,196,196,89,89,86,86,61,61,139,139,207,207,1,1,58,58,45,45,37,37,
	193,193,80,80,101,101,231,231,223,223,168,168,146,146,150,150,87,87,166,166,195,195,36,
	36,251,251,64,64,39,39,10,10,47,47,26,26,62,62,197,197,184,184,85,85,252,252,221,221,138,
	138,245,245,44,44,8,8,186,186,97,97,15,15,107,107,68,68,206,206,59,59,23,23,228,228,145,
	145,196,196,130,130,89,89,86,86,139,139,207,207},
{1,1,0,1,1,116,116,180,180,106,106,5,5,94,94,253,253,17,17,103,103,132,132,85,85,230,230,215,
	215,174,174,28,28,89,89,172,172,3,3,193,193,160,160,190,190,214,214,51,51,77,77,145,145,
	255,255,55,55,100,100,235,235,1,1,180,180,5,5,253,253,223,223,17,17,103,103,46,46,132,
	132,215,215,150,150,44,44,108,108,32,32,3,3,156,156,193,193,190,190,15,15,214,214,226,
	226,26,26,124,124,51,51,169,169,145,145,55,55,167,167,239,239,233,233,1,1,116,116,96,96,
	106,106,17,17,85,85,230,230,215,215,150,150,28,28,172,172,244,244,108,108,32,32,3,3,156,
	156,160,160,15,15,214,214,226,226,26,26,114,114,239,239,36,36,233,233,1,1,116,116,106,
	106,5,5,94,94,223,223,59,59,46,46,132,132,85,85,230,230,215,215,150,150,174,174,89,89,
	172,172,244,244,108,108,32,32,38,38,15,15,214,214,124,124,51,51,77,77,114,114,145,145,
	255,255,167,167,235,235,1,1,180,180,185,185,94,94,253,253,223,223,103,103,46,46,215,215,
	174,174,28,28,89,89,244,244,156,156,193,193,160,160,190,190,214,214,226,226,26,26,124,
	124,77,77,114,114,255,255,55,55,167,167,239,239,235,235,233,233},
{1,1,0,1,1,232,232,234,234,238,238,160,160,60,60,254,254,103,103,118,118,57,57,145,145,227,
	227,220,220,162,162,172,172,245,245,176,176,40,40,15,15,177,177,175,175,147,147,99,99,55,
	55,166,166,43,43,122,122,44,44,48,48,10,10,202,202,52,52,66,66,85,85,209,209,123,123,50,
	50,167,167,11,11,54,54,185,185,188,188,211,211,13,13,124,124,102,102,82,82,115,115,215,
	215,49,49,130,130,224,224,249,249,36,36,8,8,3,3,35,35,105,105,163,163,68,68,31,31,169,
	169,154,154,121,121,205,205,201,201,78,78,193,193,194,194,225,225,17,17,236,236,109,109,
	114,114,63,63,165,165,89,89,69,69,247,247,125,125,119,119,189,189,59,59,42,42,146,146,
	198,198,141,141,81,81,244,244,173,173,96,96,212,212,20,20,161,161,137,137,214,214,217,
	217,104,104,23,23,132,132,170,170,246,246,149,149,100,100,64,64,152,152,5,5,111,111,187,
	187,113,113,26,26,248,248,164,164,98,98,221,221,72,72,38,38,6,6,74,74,70,70,94,94,91,91,
	79,79,183,183,229,229,150,150,112,112,135,135,143,143,156,156,159,159,153,153,240,240,
	223,223,34,34,218,218,77,77,126,126,171,171,28,28,178,178,243,243,250,250},
{1,1,0,1,1,205,205,143,143,70,70,185,185,107,107,217,217,59,59,184,184,252,252,150,150,130,
	130,221,221,61,61,44,44,173,173,58,58,231,231,26,26,237,237,23,23,146,146,56,56,36,36,54,
	54,64,64,45,45,96,96,120,120,68,68,102,102,191,191,7,7,89,89,138,138,251,251,8,8,38,38,
	10,10,161,161,169,169,41,41,115,115,196,196,100,100,166,166,245,245,125,125,1,1,205,205,
	143,143,37,37,70,70,185,185,217,217,59,59,168,168,228,228,130,130,221,221,195,195,44,44,
	173,173,47,47,23,23,21,21,146,146,145,145,87,87,242,242,36,36,54,54,64,64,96,96,181,181,
	97,97,223,223,68,68,62,62,102,102,110,110,8,8,38,38,53,53,10,10,161,161,134,134,206,206,
	169,169,115,115,100,100,166,166,86,86,245,245,125,125,1,1,205,205,143,143,70,70,185,185,
	101,101,217,217,208,208,59,59,130,130,221,221,44,44,173,173,117,117,39,39,193,193,186,
	186,182,182,23,23,146,146,219,219,36,36,139,139,54,54,64,64,96,96,80,80,68,68,102,102,33,
	33,85,85,241,241,207,207,8,8,38,38,12,12,10,10,161,161,15,15,127,127,197,197,169,169,115,
	115,179,179,100,100,166,166,245,245,125,125},
{0,1,0,0,1,51,49,104,108,249,233,17,49,16,144,246,235,104,28,74,162,29,14,33,7,163,239,143,
	23,60,102,77,249,208,165,137,99,76,84,117,21,110,174,255,98,8,70,57,173,156,246,118,195,
	129,246,188,82,198,7,121,245,214,220,218,242,192,157,234,56,12,181,100,11,237,51,226,189,
	3,189,64,217,12,35,212,219,40,54,237,209,220,44,94,163,7,224,182,13,219,176,1,215,163,18,
	45,82,212,42,189,92,202,21,101,211,15,237,105,198,229,166,19,49,147,215,186,50,74,80,135,
	179,222,95,39,202,238,41,255,108,80,107,169,69,251,108,193,242,87,155,174,43,5,43,4,88,
	154,247,47,134,205,130,161,63,80,113,182,226,93,249,211,134,52,125,215,69,194,251,232,61,
	147,36,132,98,21,170,82,195,110,81,59,69,134,122,20,241,1,214,58,137,98,25,37,212,145,
	110,48,211,128,43,175,228,12,154,168,198,51,239,85,251,138,203,2,27,202,248,191,219,187,
	115,241,255,24,104,214,11,62,109,137,208,185,11,6,127,74,184,182,89,120,227,174,235,206,
	199,151,133,231,195,127,239,96,147,97,154,26,241,53,254,226,233,210,196,208,252,179,235,
	38,220,127,150,213,86,242,233,223,179,83,139,136,207,197,75},
{0,1,0,0,1,102,98,189,173,43,54,26,110,232,251,49,125,237,89,70,172,234,242,146,242,104,245,
	212,154,217,77,145,251,23,162,217,55,238,179,10,179,155,69,166,249,74,211,130,156,15,242,
	99,8,114,195,124,130,162,125,64,3,79,11,220,232,127,254,231,32,127,68,2,238,75,220,115,
	246,223,241,137,198,217,248,248,173,23,94,50,11,232,95,85,179,143,48,227,220,64,188,214,
	1,219,160,26,235,23,244,7,172,99,245,145,255,215,121,114,64,205,5,124,12,69,152,230,181,
	42,115,147,234,241,227,85,174,191,116,53,62,241,221,4,254,136,147,215,187,111,225,161,
	163,150,182,109,237,143,103,221,251,82,202,28,70,130,247,203,11,167,208,247,54,8,132,153,
	147,69,109,252,46,234,133,193,127,70,105,105,102,175,147,157,109,205,42,69,254,215,1,150,
	233,134,103,89,239,214,52,167,8,55,21,117,253,166,188,15,226,186,41,214,229,183,123,50,
	110,205,160,68,237,143,17,199,147,244,80,78,220,190,107,48,161,76,50,11,238,108,223,40,
	215,106,33,228,56,240,177,182,175,10,110,210,220,29,175,193,51,214,57,180,47,120,61,119,
	126,182,146,213,69,16,227,60,215,164,178,83,11,214,63,112,243,34,250,236,171},
{0,1,0,0,1,204,196,206,142,138,71,103,65,45,88,87,216,204,172,210,245,37,144,252,61,197,131,
	105,99,124,198,55,142,85,244,199,166,101,14,231,56,27,173,22,207,188,248,244,202,124,71,
	167,193,7,16,115,203,142,39,160,137,220,78,44,95,84,168,132,95,41,191,222,26,88,54,9,139,
	114,22,42,247,145,55,65,101,167,154,76,185,223,84,244,216,26,103,16,38,223,114,215,214,
	29,21,130,194,155,161,157,80,71,97,8,135,116,20,173,136,103,82,195,133,153,147,29,77,131,
	58,36,133,192,39,205,20,3,133,183,243,53,47,151,89,144,125,106,81,165,195,65,86,160,9,58,
	27,213,125,107,62,48,162,211,55,15,124,151,102,134,4,204,168,114,74,69,152,59,157,94,157,
	150,192,167,131,89,172,9,37,29,96,14,193,150,160,169,4,214,215,217,209,76,12,23,218,32,6,
	102,75,208,95,28,16,184,216,64,6,250,240,180,13,113,208,184,151,83,54,181,186,172,212,
	222,161,219,2,11,79,76,156,22,45,144,85,100,2,81,70,135,46,4,17,236,126,35,80,222,97,117,
	228,192,115,88,15,143,13,190,218,2,5,111,178,12,170,120,33,84,166,27,145,194,230,21,224,
	14,245,253,209,7,122,134,176,118,219},
{0,1,0,0,1,133,149,31,2,72,4,124,200,3,27,141,16,158,244,94,176,5,88,196,125,66,29,15,150,
	218,196,167,90,179,216,132,122,17,144,206,245,143,24,76,201,26,85,135,206,114,148,131,
	127,88,35,224,3,238,120,13,197,11,214,148,237,14,28,14,197,166,138,197,63,70,93,157,159,
	172,140,89,193,251,142,232,41,6,138,182,158,229,138,160,30,110,65,127,67,241,22,1,215,
	113,144,143,57,5,170,118,84,254,228,217,52,26,41,113,28,81,207,222,122,215,69,206,27,175,
	62,30,251,84,77,23,229,84,207,234,175,115,87,207,60,217,129,145,120,185,254,95,91,55,67,
	132,151,156,118,86,54,145,223,86,194,242,71,205,19,27,170,234,53,20,87,147,215,90,110,
	144,87,187,87,103,73,237,204,109,56,241,200,206,121,182,9,140,179,1,214,205,60,165,14,70,
	40,150,56,35,17,192,176,151,196,186,227,130,121,227,232,89,53,96,238,94,222,77,165,139,
	173,209,139,64,128,151,224,220,214,138,88,50,61,196,52,73,242,63,64,61,223,86,222,254,
	109,38,234,192,156,207,102,8,92,86,40,8,187,193,62,139,192,238,50,232,169,161,197,23,25,
	139,57,186,85,109,100,130,18,15,228,50,36,175,44,59,227},
{0,1,0,0,1,23,55,124,8,244,64,59,56,157,1,167,205,41,44,231,71,95,1,7,8,114,143,91,141,146,
	112,36,53,130,152,191,216,133,1,21,64,160,210,70,160,66,149,10,164,100,120,78,23,48,223,
	131,47,225,197,146,123,78,79,163,215,1,2,8,98,205,12,149,144,103,199,217,103,96,62,201,
	31,70,153,177,138,68,119,215,249,27,159,169,228,205,152,215,49,8,153,214,1,150,105,206,
	88,33,22,89,247,171,207,87,14,28,176,65,181,10,225,99,15,152,153,249,217,112,86,98,214,1,
	4,207,192,64,189,21,195,143,80,31,14,172,203,156,224,220,239,130,172,185,61,76,1,252,142,
	134,23,159,72,34,221,217,79,114,213,42,193,123,87,221,177,152,153,246,214,23,163,88,91,
	38,186,143,78,119,206,214,104,201,151,64,79,43,214,215,1,196,27,26,248,138,144,17,118,9,
	117,162,145,70,104,139,34,197,84,208,7,77,122,69,235,29,1,107,204,219,130,68,171,167,83,
	188,85,79,78,246,130,164,196,66,222,189,215,151,86,165,5,49,143,80,134,11,233,1,16,195,
	217,244,136,141,192,139,222,3,113,43,205,12,219,108,147,70,208,124,75,72,84,35,132,51,
	220,55,155,94,170,174,69,226,11,147,255},
{0,1,0,0,1,46,110,237,32,251,116,51,83,53,128,242,180,213,108,91,58,120,19,242,45,179,106,
	189,249,123,69,233,210,242,148,149,45,228,24,179,37,177,223,253,127,246,43,225,220,235,
	199,30,179,101,109,37,31,218,252,112,69,214,220,168,9,93,186,222,88,101,127,233,39,123,
	150,230,241,226,75,163,49,237,158,209,181,171,147,131,37,101,51,239,203,182,67,71,58,127,
	73,215,214,232,168,7,202,72,101,238,97,135,231,12,74,106,211,39,66,164,220,58,227,147,
	215,222,14,20,47,39,65,129,62,208,82,151,144,32,253,168,241,235,97,225,26,230,202,210,
	127,190,182,174,136,41,92,159,184,251,58,98,104,11,177,251,90,119,193,37,50,194,107,34,
	11,215,69,101,22,192,27,168,108,255,155,110,200,81,117,216,45,174,37,241,140,184,142,214,
	215,134,198,234,39,21,154,180,212,168,141,184,254,144,192,191,6,80,137,106,46,253,198,
	213,179,56,25,201,97,237,184,119,147,164,85,45,175,214,11,151,84,13,33,226,45,97,204,211,
	219,82,116,84,88,180,190,83,242,18,61,110,97,112,15,255,58,195,212,32,137,14,27,116,230,
	251,136,39,182,34,145,239,184,74,46,237,75,171,89,190,154,110,155,182,203,199,241},
{0,1,0,0,1,92,220,147,128,11,19,46,178,159,19,69,24,126,32,136,180,91,24,61,39,220,93,102,
	245,65,44,116,240,251,210,83,106,149,93,56,97,237,118,129,147,166,173,204,36,180,183,199,
	242,124,227,253,213,75,242,216,38,79,11,141,117,129,31,118,193,184,41,10,113,251,176,18,
	11,230,250,115,54,110,83,203,237,142,100,47,31,170,221,106,111,241,75,231,91,179,203,1,
	215,175,244,96,230,210,230,109,114,136,179,59,46,169,219,46,203,131,96,103,234,69,152,
	145,35,213,241,66,181,18,72,36,116,176,223,151,14,58,53,68,165,242,122,96,7,110,249,25,
	69,190,243,201,128,75,116,62,168,161,125,59,9,237,213,110,165,55,254,155,251,71,169,153,
	147,72,33,165,85,35,146,253,236,182,136,199,110,191,149,68,224,127,155,159,252,1,214,38,
	253,50,167,185,190,100,195,190,199,160,232,170,89,127,83,44,32,144,222,38,134,182,104,66,
	92,155,32,186,101,22,185,182,113,172,238,78,220,15,113,210,182,10,122,201,107,106,169,
	208,36,26,224,88,192,241,49,25,141,228,37,241,35,146,176,100,180,44,80,150,122,27,84,43,
	127,45,120,127,170,221,118,12,59,189,179,179,224,185,21,98,242,163,251,237,246},
{0,1,0,0,1,184,165,118,58,176,45,169,195,40,117,122,37,219,38,62,192,52,181,125,70,224,101,
	84,27,89,16,96,134,1,253,61,222,121,107,245,217,82,73,168,170,88,192,145,29,185,7,230,1,
	183,86,151,56,18,8,193,95,220,78,108,137,252,229,150,13,130,166,129,114,212,140,39,35,36,
	80,144,222,1,180,93,130,15,76,154,174,244,24,59,21,1,32,198,255,1,190,214,1,196,111,237,
	131,41,27,138,250,25,64,242,9,244,152,144,120,223,133,178,197,153,147,135,85,128,143,233,
	82,231,187,127,204,26,81,125,161,23,115,18,160,211,67,114,153,105,177,97,113,100,208,57,
	33,186,84,54,143,14,151,4,26,1,106,137,30,240,139,129,23,85,157,69,152,51,74,223,20,167,
	93,44,12,1,116,24,217,202,226,19,124,1,46,239,211,215,1,110,216,206,236,251,22,124,79,88,
	53,243,87,15,218,205,92,179,65,115,54,167,78,48,119,60,47,228,14,173,205,150,2,74,148,
	126,207,11,79,6,193,19,70,128,55,235,212,71,182,153,55,194,145,166,173,42,164,191,63,102,
	64,154,90,92,172,241,142,172,78,209,89,245,102,112,188,8,161,202,158,25,103,152,103,34,
	99,198,200,160,79,171,162,225,247,248,123},
{0,1,0,0,1,109,87,197,232,207,234,132,69,185,24,139,238,220,3,51,181,59,93,8,161,86,254,230,
	116,122,201,5,147,117,34,108,107,44,129,64,102,75,196,227,196,180,190,224,159,17,11,112,
	181,56,128,252,233,19,70,113,31,11,214,70,204,18,36,22,99,173,205,246,195,136,206,175,
	206,156,147,106,46,47,225,92,205,170,91,9,205,80,104,28,69,231,177,131,8,107,164,215,214,
	19,41,221,240,235,231,93,120,24,217,10,111,94,129,47,255,165,72,186,18,215,69,248,71,129,
	23,217,142,25,100,221,250,9,188,104,98,54,143,163,219,83,138,3,25,55,242,50,138,94,11,96,
	19,174,117,23,115,253,32,66,176,33,171,155,86,61,92,128,143,35,149,147,215,143,65,131},
	162,208,249,77,220,191,123,25,64,22,64,49,12,252,119,23,216,214,215,68,126,24,53,146,183,
	156,93,191,239,228,129,142,105,130,93,68,236,163,49,132,18,172,251,38,128,226,33,130,166,
	118,141,203,139,62,25,220,214,247,216,18,8,43,21,130,71,178,10,24,77,48,204,246,43,103,
	237,92,169,217,245,199,207,189,7,146,243,28,19,42,65,249,189,110,160,125,70,210,197,98,
	134,128,17,182,114,213,87,5,92,241,167,127,244,124,179},
{0,1,0,0,1,218,174,51,135,108,6,77,72,194,156,233,20,141,156,79,40,218,94,45,120,235,13,219,
	12,27,181,94,66,181,236,152,52,135,132,37,228,89,249,81,239,80,134,88,107,132,201,250,
	107,250,5,121,78,210,182,84,191,78,79,34,150,3,6,119,138,186,101,251,234,145,246,209,255,
	17,149,208,7,33,183,83,127,144,252,193,225,109,110,3,159,191,126,15,177,252,243,1,215,17,
	243,37,63,153,229,77,126,199,110,168,57,145,166,63,152,192,47,183,94,152,153,86,34,155,
	251,112,26,5,20,97,52,177,87,72,159,62,168,242,238,15,163,85,161,186,214,194,226,28,31,
	209,77,153,57,58,53,195,21,117,151,117,111,26,104,236,3,213,241,14,231,152,153,171,223,
	164,206,232,237,5,91,47,240,136,179,85,123,182,50,231,178,119,145,1,214,45,187,28,178,
	101,60,89,245,187,79,240,156,171,139,237,203,39,40,201,31,15,115,228,215,81,28,78,60,184,
	41,222,33,150,49,111,132,79,78,196,112,75,242,241,175,164,89,229,58,125,26,207,225,66,
	149,120,214,17,13,97,56,223,43,127,227,184,121,150,54,197,123,141,91,215,53,61,39,193,
	189,179,254,173,223,214,41,85,98,193,102,215,56,214,61,62,215},
{0,1,0,0,1,169,65,204,38,142,96,85,245,137,181,71,185,166,193,41,95,82,107,39,182,216,59,50,
	238,205,111,223,115,161,84,53,133,212,252,97,110,88,233,44,131,254,109,143,236,150,161,
	192,102,157,182,2,120,13,33,130,178,214,220,57,243,231,211,68,6,237,184,106,187,144,235,
	36,22,145,54,227,232,166,144,6,191,70,250,236,63,121,116,26,102,125,27,183,229,173,222,
	214,1,110,95,197,71,228,4,251,2,81,117,139,131,32,35,29,62,23,126,16,179,147,215,194,221,
	194,107,40,178,191,198,196,9,221,20,223,145,251,58,253,63,14,239,180,165,149,121,100,9,
	15,125,74,117,56,157,168,241,175,234,183,64,115,14,27,108,76,241,20,47,217,243,215,69,60,
	250,10,135,229,180,89,173,245,88,135,231,111,187,32,52,54,151,121,240,215,1,87,142,237,
	133,207,216,46,170,16,186,4,242,68,209,181,209,86,22,89,193,116,113,91,52,154,33,61,76,
	101,127,8,240,151,51,29,127,214,11,218,146,218,252,46,40,52,126,204,138,224,190,81,10,26,
	85,159,40,47,202,37,179,222,174,190,57,206,65,230,122,13,146,150,15,57,201,242,45,192,
	226,230,60,176,253,60,66,84,255,106,118,63,141,187,72,31,229}
	};
	


main(){
int i,j;







}

