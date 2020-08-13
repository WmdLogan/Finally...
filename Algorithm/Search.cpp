//
// Created by logan on 2020/8/12.
//
// 1091. Shortest Path in Binary Matrix(Medium)
// 279. Perfect Squares (Medium)
// 127. Word Ladder (Medium)
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
// 1091. Shortest Path in Binary Matrix(Medium)
    int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
        // corner case
        const int N = grid.size();
        if (grid[0][0] || grid[N - 1][N - 1]) return -1;

        const vector<vector<int>> DIRS{{-1, 0},
                                       {-1, 1},
                                       {0,  1},
                                       {1,  1},
                                       {1,  0},
                                       {1,  -1},
                                       {0,  -1},
                                       {-1, -1}};

        using P = pair<int, int>;
        queue<P> q;
        q.emplace(0, 0);
        grid[0][0] = 2; // visited;

        int distance = 1;
        while (not q.empty()) {
            int size = q.size();
            while (size--) {
                auto[x, y] = q.front();
                q.pop();
                if (x == N - 1 && y == N - 1)
                    return distance;

                for (const auto &d : DIRS) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx < 0 || dy < 0 || dx >= N || dy >= N || grid[dy][dx] != 0)
                        continue;
                    grid[dy][dx] = 2;
                    q.emplace(dx, dy);
                }
            }
            ++distance;
        }
        return -1;
    }

// 279. Perfect Squares (Medium)
//动态规划
    int numSquares_dp(int n) {
        vector<int> result(n + 1, 0x7FFFFFFF); // 每个数的最优解都存在result数组里
        result[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; i - j * j >= 0; j++) {  // 观察比N小的数，且符合N = IxI + N'的数值
                result[i] = min(result[i], result[i - j * j] + 1); // 把最优解（最小值）+ 1 写入result
            }
        }
        return result[n];
    }
//将此题目抽象为，要从n走到0，每次跨越的距离只能为平方数，求最少的跨越次数。很自然用标准的BFS去解决
    /*返回小于n的平方序列: 1, 4, 9...*/
    vector<int> getSquares(int n) {
        vector<int> res;
        for (int i = 1; i * i <= n; ++i) {
            res.emplace_back(i * i);
        }
        return res;
    }

    int numSquares(int n) {
        vector<int> squares = getSquares(n);
        vector<bool> visited(n + 1);    //记录已访问过的节点
        queue<int> q;

        q.push(n);
        int res = 0;
        visited[n] = true;
        while (!q.empty()) {
            int size = q.size();
            res++;
            while (size--) {
                int curr = q.front();
                q.pop();
                /*每次跨越的间隔为平方数*/
                for (int num: squares) {
                    int next = curr - num;
                    if (next < 0) {
                        break;
                    }
                    if (next == 0) {
                        return res;
                    }
                    if (visited[next]) {
                        continue;
                    }
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        return n;
    }

// 127. Word Ladder (Medium)
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        unordered_set<string> wordset{wordList.begin(), wordList.end()}; //处理endWord不在wordList中的特殊情况
        if (wordset.find(endWord) == wordset.end()) return 0;
        unordered_set<string> begintoend{beginWord}; //用来存放从起点开始，匹配到的单词
        unordered_set<string> endtobegin{endWord};//用来存放从终点开始，匹配到的单词

        queue<string> beginQ; //从起点开始，可能的单词入队
        queue<string> endQ; //从终点开始，可能的单词入队
        beginQ.push(beginWord);
        endQ.push(endWord);

        int depth = biDirectionBfs( wordset, beginQ, endQ, begintoend, endtobegin);

        return depth;
    }

    int biDirectionBfs(unordered_set<string> &wordset,
                       queue<string> &beginQ, queue<string> &endQ,
                       unordered_set<string> &begintoend,
                       unordered_set<string> &endtobegin) {
        int depth = 0;
        while (!beginQ.empty() && !endQ.empty()) {  //任何一个队列为空，都是线索断了的意思，所以要用&&
            int flag_begintoend = 1;
            if (beginQ.size() > endQ.size()) { //这里选择一个较短的队列进行搜索
                swap(beginQ, endQ); //交换的意义在于，后面代码我们只准备用一个队列变量来进行搜索，所以要把较短的队列统一到beginQ上，便于后面做搜索，当然也可以重新写个bfs函数，就不需要交换了。
                flag_begintoend = 0; //flag用于判断下方代码while使用的BeginQ是真的BeginQ，还是假的BeginQ
            } else {
                flag_begintoend = 1;
            }

            int size = beginQ.size(); //当前较短队列中存放的元素个数
            depth++;
            while (size--) {
                string hop = beginQ.front();
                beginQ.pop();

                for (int i = 0; i < hop.size(); i++) {
                    string w_change = hop;
                    for (char j = 'a'; j <= 'z'; j++) {
                        w_change[i] = j;
                        if (wordset.find(w_change) == wordset.end()) {
                            continue;
                        }
                        //排除重复遍历单词
                        //当前beginQ是begintoend的路径上的元素
                        if (flag_begintoend && begintoend.find(w_change) != begintoend.end())
                            continue;
                        //当前beginQ是endtobegin的路径上的元素
                        if (!flag_begintoend && endtobegin.find(w_change) != endtobegin.end())
                            continue;

                        if (flag_begintoend) {
                            begintoend.insert(w_change);
                            if (endtobegin.find(w_change) != endtobegin.end()) return depth + 1;
                        } else {
                            endtobegin.insert(w_change);
                            if (begintoend.find(w_change) != begintoend.end()) return depth + 1;
                        }

                        beginQ.push(w_change);

                    }
                }
            }
            //最后还是需要还原队列对应关系
            if (!flag_begintoend) {
                swap(beginQ, endQ);
            }
        }
        return 0;
    }
};

int main() {
    Solution s;
    vector<string> word = {"ricky", "grind", "cubic", "panic", "lover", "farce", "gofer", "sales", "flint", "omens",
                           "lipid", "briny", "cloth", "anted", "slime", "oaten", "harsh", "touts", "stoop", "cabal",
                           "lazed", "elton", "skunk", "nicer", "pesky", "kusch", "bused", "kinda", "tunis", "enjoy",
                           "aches", "prowl", "babar", "rooms", "burst", "slush", "pines", "urine", "pinky", "bayed",
                           "mania", "light", "flare", "wares", "women", "verne", "moron", "shine", "bluer", "zeros",
                           "bleak", "brief", "tamra", "vasts", "jamie", "lairs", "penal", "worst", "yowls", "pills",
                           "taros", "addle", "alyce", "creep", "saber", "floyd", "cures", "soggy", "vexed", "vilma",
                           "cabby", "verde", "euler", "cling", "wanna", "jenny", "donor", "stole", "sakha", "blake",
                           "sanes", "riffs", "forge", "horus", "sered", "piked", "prosy", "wases", "glove", "onset",
                           "spake", "benin", "talks", "sites", "biers", "wendy", "dante", "allan", "haven", "nears",
                           "shaka", "sloth", "perky", "spear", "spend", "clint", "dears", "sadly", "units", "vista",
                           "hinds", "marat", "natal", "least", "bough", "pales", "boole", "ditch", "greys", "slunk",
                           "bitch", "belts", "sense", "skits", "monty", "yawns", "music", "hails", "alien", "gibes",
                           "lille", "spacy", "argot", "wasps", "drubs", "poops", "bella", "clone", "beast", "emend",
                           "iring", "start", "darla", "bells", "cults", "dhaka", "sniff", "seers", "bantu", "pages",
                           "fever", "tacky", "hoses", "strop", "climb", "pairs", "later", "grant", "raven", "stael",
                           "drips", "lucid", "awing", "dines", "balms", "della", "galen", "toned", "snips", "shady",
                           "chili", "fears", "nurse", "joint", "plump", "micky", "lions", "jamal", "queer", "ruins",
                           "frats", "spoof", "semen", "pulps", "oldie", "coors", "rhone", "papal", "seals", "spans",
                           "scaly", "sieve", "klaus", "drums", "tided", "needs", "rider", "lures", "treks", "hares",
                           "liner", "hokey", "boots", "primp", "laval", "limes", "putts", "fonda", "damon", "pikes",
                           "hobbs", "specs", "greet", "ketch", "braid", "purer", "tsars", "berne", "tarts", "clean",
                           "grate", "trips", "chefs", "timex", "vicky", "pares", "price", "every", "beret", "vices",
                           "jodie", "fanny", "mails", "built", "bossy", "farms", "pubic", "gongs", "magma", "quads",
                           "shell", "jocks", "woods", "waded", "parka", "jells", "worse", "diner", "risks", "bliss",
                           "bryan", "terse", "crier", "incur", "murky", "gamed", "edges", "keens", "bread", "raced",
                           "vetch", "glint", "zions", "porno", "sizes", "mends", "ached", "allie", "bands", "plank",
                           "forth", "fuels", "rhyme", "wimpy", "peels", "foggy", "wings", "frill", "edgar", "slave",
                           "lotus", "point", "hints", "germs", "clung", "limed", "loafs", "realm", "myron", "loopy",
                           "plush", "volts", "bimbo", "smash", "windy", "sours", "choke", "karin", "boast", "whirr",
                           "tiber", "dimes", "basel", "cutes", "pinto", "troll", "thumb", "decor", "craft", "tared",
                           "split", "josue", "tramp", "screw", "label", "lenny", "apses", "slept", "sikhs", "child",
                           "bouts", "cites", "swipe", "lurks", "seeds", "fists", "hoard", "steed", "reams", "spoil",
                           "diego", "peale", "bevel", "flags", "mazes", "quart", "snipe", "latch", "lards", "acted",
                           "falls", "busby", "holed", "mummy", "wrong", "wipes", "carlo", "leers", "wails", "night",
                           "pasty", "eater", "flunk", "vedas", "curse", "tyros", "mirth", "jacky", "butte", "wired",
                           "fixes", "tares", "vague", "roved", "stove", "swoon", "scour", "coked", "marge", "cants",
                           "comic", "corns", "zilch", "typos", "lives", "truer", "comma", "gaily", "teals", "witty",
                           "hyper", "croat", "sways", "tills", "hones", "dowel", "llano", "clefs", "fores", "cinch",
                           "brock", "vichy", "bleed", "nuder", "hoyle", "slams", "macro", "arabs", "tauts", "eager",
                           "croak", "scoop", "crime", "lurch", "weals", "fates", "clipt", "teens", "bulls", "domed",
                           "ghana", "culls", "frame", "hanky", "jared", "swain", "truss", "drank", "lobby", "lumps",
                           "pansy", "whews", "saris", "trite", "weeps", "dozes", "jeans", "flood", "chimu", "foxes",
                           "gelds", "sects", "scoff", "poses", "mares", "famed", "peers", "hells", "laked", "zests",
                           "wring", "steal", "snoot", "yodel", "scamp", "ellis", "bandy", "marry", "jives", "vises",
                           "blurb", "relay", "patch", "haley", "cubit", "heine", "place", "touch", "grain", "gerry",
                           "badly", "hooke", "fuchs", "savor", "apron", "judge", "loren", "britt", "smith", "tammy",
                           "altar", "duels", "huber", "baton", "dived", "apace", "sedan", "basts", "clark", "mired",
                           "perch", "hulks", "jolly", "welts", "quack", "spore", "alums", "shave", "singe", "lanny",
                           "dread", "profs", "skeet", "flout", "darin", "newed", "steer", "taine", "salvo", "mites",
                           "rules", "crash", "thorn", "olive", "saves", "yawed", "pique", "salon", "ovens", "dusty",
                           "janie", "elise", "carve", "winds", "abash", "cheep", "strap", "fared", "discs", "poxed",
                           "hoots", "catch", "combo", "maize", "repay", "mario", "snuff", "delve", "cored", "bards",
                           "sudan", "shuns", "yukon", "jowls", "wayne", "torus", "gales", "creek", "prove", "needy",
                           "wisps", "terri", "ranks", "books", "dicky", "tapes", "aping", "padre", "roads", "nines",
                           "seats", "flats", "rains", "moira", "basic", "loves", "pulls", "tough", "gills", "codes",
                           "chest", "teeny", "jolts", "woody", "flame", "asked", "dulls", "hotly", "glare", "mucky",
                           "spite", "flake", "vines", "lindy", "butts", "froth", "beeps", "sills", "bunny", "flied",
                           "shaun", "mawed", "velds", "voled", "doily", "patel", "snake", "thigh", "adler", "calks",
                           "desks", "janus", "spunk", "baled", "match", "strip", "hosed", "nippy", "wrest", "whams",
                           "calfs", "sleet", "wives", "boars", "chain", "table", "duked", "riped", "edens", "galas",
                           "huffs", "biddy", "claps", "aleut", "yucks", "bangs", "quids", "glenn", "evert", "drunk",
                           "lusts", "senna", "slate", "manet", "roted", "sleep", "loxes", "fluky", "fence", "clamp",
                           "doted", "broad", "sager", "spark", "belch", "mandy", "deana", "beyer", "hoist", "leafy",
                           "levee", "libel", "tonic", "aloes", "steam", "skews", "tides", "stall", "rifts", "saxon",
                           "mavis", "asama", "might", "dotes", "tangs", "wroth", "kited", "salad", "liens", "clink",
                           "glows", "balky", "taffy", "sided", "sworn", "oasis", "tenth", "blurt", "tower", "often",
                           "walsh", "sonny", "andes", "slump", "scans", "boded", "chive", "finer", "ponce", "prune",
                           "sloes", "dined", "chums", "dingo", "harte", "ahead", "event", "freer", "heart", "fetch",
                           "sated", "soapy", "skins", "royal", "cuter", "loire", "minot", "aisle", "horny", "slued",
                           "panel", "eight", "snoop", "pries", "clive", "pored", "wrist", "piped", "daren", "cells",
                           "parks", "slugs", "cubed", "highs", "booze", "weary", "stain", "hoped", "finny", "weeds",
                           "fetid", "racer", "tasks", "right", "saint", "shahs", "basis", "refer", "chart", "seize",
                           "lulls", "slant", "belay", "clots", "jinny", "tours", "modes", "gloat", "dunks", "flute",
                           "conch", "marts", "aglow", "gayer", "lazes", "dicks", "chime", "bears", "sharp", "hatch",
                           "forms", "terry", "gouda", "thins", "janet", "tonya", "axons", "sewed", "danny", "rowdy",
                           "dolts", "hurry", "opine", "fifty", "noisy", "spiky", "humid", "verna", "poles", "jayne",
                           "pecos", "hooky", "haney", "shams", "snots", "sally", "ruder", "tempe", "plunk", "shaft",
                           "scows", "essie", "dated", "fleet", "spate", "bunin", "hikes", "sodas", "filly", "thyme",
                           "fiefs", "perks", "chary", "kiths", "lidia", "lefty", "wolff", "withe", "three", "crawl",
                           "wotan", "brown", "japed", "tolls", "taken", "threw", "crave", "clash", "layer", "tends",
                           "notes", "fudge", "musky", "bawdy", "aline", "matts", "shirr", "balks", "stash", "wicks",
                           "crepe", "foods", "fares", "rotes", "party", "petty", "press", "dolly", "mangy", "leeks",
                           "silly", "leant", "nooks", "chapt", "loose", "caged", "wages", "grist", "alert", "sheri",
                           "moody", "tamps", "hefts", "souls", "rubes", "rolex", "skulk", "veeps", "nonce", "state",
                           "level", "whirl", "bight", "grits", "reset", "faked", "spiny", "mixes", "hunks", "major",
                           "missy", "arius", "damns", "fitly", "caped", "mucus", "trace", "surat", "lloyd", "furry",
                           "colin", "texts", "livia", "reply", "twill", "ships", "peons", "shear", "norms", "jumbo",
                           "bring", "masks", "zippy", "brine", "dorks", "roded", "sinks", "river", "wolfs", "strew",
                           "myths", "pulpy", "prank", "veins", "flues", "minus", "phone", "banns", "spell", "burro",
                           "brags", "boyle", "lambs", "sides", "knees", "clews", "aired", "skirt", "heavy", "dimer",
                           "bombs", "scums", "hayes", "chaps", "snugs", "dusky", "loxed", "ellen", "while", "swank",
                           "track", "minim", "wiled", "hazed", "roofs", "cantu", "sorry", "roach", "loser", "brass",
                           "stint", "jerks", "dirks", "emory", "campy", "poise", "sexed", "gamer", "catty", "comte",
                           "bilbo", "fasts", "ledge", "drier", "idles", "doors", "waged", "rizal", "pured", "weirs",
                           "crisp", "tasty", "sored", "palmy", "parts", "ethel", "unify", "crows", "crest", "udder",
                           "delis", "punks", "dowse", "totes", "emile", "coded", "shops", "poppa", "pours", "gushy",
                           "tiffs", "shads", "birds", "coils", "areas", "boons", "hulls", "alter", "lobes", "pleat",
                           "depth", "fires", "pones", "serra", "sweat", "kline", "malay", "ruled", "calve", "tired",
                           "drabs", "tubed", "wryer", "slung", "union", "sonya", "aided", "hewed", "dicey", "grids",
                           "nixed", "whits", "mills", "buffs", "yucky", "drops", "ready", "yuppy", "tweet", "napes",
                           "cadre", "teach", "rasps", "dowdy", "hoary", "canto", "posed", "dumbo", "kooks", "reese",
                           "snaky", "binge", "byron", "phony", "safer", "friar", "novel", "scale", "huron", "adorn",
                           "carla", "fauna", "myers", "hobby", "purse", "flesh", "smock", "along", "boils", "pails",
                           "times", "panza", "lodge", "clubs", "colby", "great", "thing", "peaks", "diana", "vance",
                           "whets", "bergs", "sling", "spade", "soaks", "beach", "traps", "aspen", "romps", "boxed",
                           "fakir", "weave", "nerds", "swazi", "dotty", "curls", "diver", "jonas", "waite", "verbs",
                           "yeast", "lapel", "barth", "soars", "hooks", "taxed", "slews", "gouge", "slags", "chang",
                           "chafe", "saved", "josie", "syncs", "fonds", "anion", "actor", "seems", "pyrex", "isiah",
                           "glued", "groin", "goren", "waxes", "tonia", "whine", "scads", "knelt", "teaks", "satan",
                           "tromp", "spats", "merry", "wordy", "stake", "gland", "canal", "donna", "lends", "filed",
                           "sacks", "shied", "moors", "paths", "older", "pooch", "balsa", "riced", "facet", "decaf",
                           "attic", "elder", "akron", "chomp", "chump", "picky", "money", "sheer", "bolls", "crabs",
                           "dorms", "water", "veers", "tease", "dummy", "dumbs", "lethe", "halls", "rifer", "demon",
                           "fucks", "whips", "plops", "fuses", "focal", "taces", "snout", "edict", "flush", "burps",
                           "dawes", "lorry", "spews", "sprat", "click", "deann", "sited", "aunts", "quips", "godly",
                           "pupil", "nanny", "funks", "shoon", "aimed", "stacy", "helms", "mints", "banks", "pinch",
                           "local", "twine", "pacts", "deers", "halos", "slink", "preys", "potty", "ruffs", "pusan",
                           "suits", "finks", "slash", "prods", "dense", "edsel", "heeds", "palls", "slats", "snits",
                           "mower", "rares", "ailed", "rouge", "ellie", "gated", "lyons", "duded", "links", "oaths",
                           "letha", "kicks", "firms", "gravy", "month", "kongo", "mused", "ducal", "toted", "vocal",
                           "disks", "spied", "studs", "macao", "erick", "coupe", "starr", "reaps", "decoy", "rayon",
                           "nicks", "breed", "cosby", "haunt", "typed", "plain", "trays", "muled", "saith", "drano",
                           "cower", "snows", "buses", "jewry", "argus", "doers", "flays", "swish", "resin", "boobs",
                           "sicks", "spies", "bails", "wowed", "mabel", "check", "vapid", "bacon", "wilda", "ollie",
                           "loony", "irked", "fraud", "doles", "facts", "lists", "gazed", "furls", "sunks", "stows",
                           "wilde", "brick", "bowed", "guise", "suing", "gates", "niter", "heros", "hyped", "clomp",
                           "never", "lolls", "rangy", "paddy", "chant", "casts", "terns", "tunas", "poker", "scary",
                           "maims", "saran", "devon", "tripe", "lingo", "paler", "coped", "bride", "voted", "dodge",
                           "gross", "curds", "sames", "those", "tithe", "steep", "flaks", "close", "swops", "stare",
                           "notch", "prays", "roles", "crush", "feuds", "nudge", "baned", "brake", "plans", "weepy",
                           "dazed", "jenna", "weiss", "tomes", "stews", "whist", "gibed", "death", "clank", "cover",
                           "peeks", "quick", "abler", "daddy", "calls", "scald", "lilia", "flask", "cheer", "grabs",
                           "megan", "canes", "jules", "blots", "mossy", "begun", "freak", "caved", "hello", "hades",
                           "theed", "wards", "darcy", "malta", "peter", "whorl", "break", "downs", "odder", "hoofs",
                           "kiddo", "macho", "fords", "liked", "flees", "swing", "elect", "hoods", "pluck", "brook",
                           "astir", "bland", "sward", "modal", "flown", "ahmad", "waled", "craps", "cools", "roods",
                           "hided", "plath", "kings", "grips", "gives", "gnats", "tabby", "gauls", "think", "bully",
                           "fogey", "sawed", "lints", "pushy", "banes", "drake", "trail", "moral", "daley", "balds",
                           "chugs", "geeky", "darts", "soddy", "haves", "opens", "rends", "buggy", "moles", "freud",
                           "gored", "shock", "angus", "puree", "raves", "johns", "armed", "packs", "minis", "reich",
                           "slots", "totem", "clown", "popes", "brute", "hedge", "latin", "stoke", "blend", "pease",
                           "rubik", "greer", "hindi", "betsy", "flows", "funky", "kelli", "humps", "chewy", "welds",
                           "scowl", "yells", "cough", "sasha", "sheaf", "jokes", "coast", "words", "irate", "hales",
                           "camry", "spits", "burma", "rhine", "bends", "spill", "stubs", "power", "voles", "learn",
                           "knoll", "style", "twila", "drove", "dacca", "sheen", "papas", "shale", "jones", "duped",
                           "tunny", "mouse", "floss", "corks", "skims", "swaps", "inned", "boxer", "synch", "skies",
                           "strep", "bucks", "belau", "lower", "flaky", "quill", "aural", "rufus", "floes", "pokes",
                           "sends", "sates", "dally", "boyer", "hurts", "foyer", "gowns", "torch", "luria", "fangs",
                           "moats", "heinz", "bolts", "filet", "firth", "begot", "argue", "youth", "chimp", "frogs",
                           "kraft", "smite", "loges", "loons", "spine", "domes", "pokey", "timur", "noddy", "doggy",
                           "wades", "lanes", "hence", "louts", "turks", "lurid", "goths", "moist", "bated", "giles",
                           "stood", "winos", "shins", "potts", "brant", "vised", "alice", "rosie", "dents", "babes",
                           "softy", "decay", "meats", "tanya", "rusks", "pasts", "karat", "nuked", "gorge", "kinks",
                           "skull", "noyce", "aimee", "watch", "cleat", "stuck", "china", "testy", "doses", "safes",
                           "stage", "bayes", "twins", "limps", "denis", "chars", "flaps", "paces", "abase", "grays",
                           "deans", "maria", "asset", "smuts", "serbs", "whigs", "vases", "robyn", "girls", "pents",
                           "alike", "nodal", "molly", "swigs", "swill", "slums", "rajah", "bleep", "beget", "thanh",
                           "finns", "clock", "wafts", "wafer", "spicy", "sorer", "reach", "beats", "baker", "crown",
                           "drugs", "daisy", "mocks", "scots", "fests", "newer", "agate", "drift", "marta", "chino",
                           "flirt", "homed", "bribe", "scram", "bulks", "servo", "vesta", "divas", "preps", "naval",
                           "tally", "shove", "ragas", "blown", "droll", "tryst", "lucky", "leech", "lines", "sires",
                           "pyxed", "taper", "trump", "payee", "midge", "paris", "bored", "loads", "shuts", "lived",
                           "swath", "snare", "boned", "scars", "aeons", "grime", "writs", "paige", "rungs", "blent",
                           "signs", "davis", "dials", "daubs", "rainy", "fawns", "wrier", "golds", "wrath", "ducks",
                           "allow", "hosea", "spike", "meals", "haber", "muses", "timed", "broom", "burks", "louis",
                           "gangs", "pools", "vales", "altai", "elope", "plied", "slain", "chasm", "entry", "slide",
                           "bawls", "title", "sings", "grief", "viola", "doyle", "peach", "davit", "bench", "devil",
                           "latex", "miles", "pasha", "tokes", "coves", "wheel", "tried", "verdi", "wanda", "sivan",
                           "prior", "fryer", "plots", "kicky", "porch", "shill", "coats", "borne", "brink", "pawed",
                           "erwin", "tense", "stirs", "wends", "waxen", "carts", "smear", "rival", "scare", "phase",
                           "bragg", "crane", "hocks", "conan", "bests", "dares", "molls", "roots", "dunes", "slips",
                           "waked", "fours", "bolds", "slosh", "yemen", "poole", "solid", "ports", "fades", "legal",
                           "cedes", "green", "curie", "seedy", "riper", "poled", "glade", "hosts", "tools", "razes",
                           "tarry", "muddy", "shims", "sword", "thine", "lasts", "bloat", "soled", "tardy", "foots",
                           "skiff", "volta", "murks", "croci", "gooks", "gamey", "pyxes", "poems", "kayla", "larva",
                           "slaps", "abuse", "pings", "plows", "geese", "minks", "derby", "super", "inked", "manic",
                           "leaks", "flops", "lajos", "fuzes", "swabs", "twigs", "gummy", "pyres", "shrew", "islet",
                           "doled", "wooly", "lefts", "hunts", "toast", "faith", "macaw", "sonia", "leafs", "colas",
                           "conks", "altos", "wiped", "scene", "boors", "patsy", "meany", "chung", "wakes", "clear",
                           "ropes", "tahoe", "zones", "crate", "tombs", "nouns", "garth", "puked", "chats", "hanks",
                           "baked", "binds", "fully", "soaps", "newel", "yarns", "puers", "carps", "spelt", "lully",
                           "towed", "scabs", "prime", "blest", "patty", "silky", "abner", "temps", "lakes", "tests",
                           "alias", "mines", "chips", "funds", "caret", "splat", "perry", "turds", "junks", "cramp",
                           "saned", "peary", "snarl", "fired", "stung", "nancy", "bulge", "styli", "seams", "hived",
                           "feast", "triad", "jaded", "elvin", "canny", "birth", "routs", "rimed", "pusey", "laces",
                           "taste", "basie", "malls", "shout", "prier", "prone", "finis", "claus", "loops", "heron",
                           "frump", "spare", "menus", "ariel", "crams", "bloom", "foxed", "moons", "mince", "mixed",
                           "piers", "deres", "tempt", "dryer", "atone", "heats", "dario", "hawed", "swims", "sheet",
                           "tasha", "dings", "clare", "aging", "daffy", "wried", "foals", "lunar", "havel", "irony",
                           "ronny", "naves", "selma", "gurus", "crust", "percy", "murat", "mauro", "cowed", "clang",
                           "biker", "harms", "barry", "thump", "crude", "ulnae", "thong", "pager", "oases", "mered",
                           "locke", "merle", "soave", "petal", "poser", "store", "winch", "wedge", "inlet", "nerdy",
                           "utter", "filth", "spray", "drape", "pukes", "ewers", "kinds", "dates", "meier", "tammi",
                           "spoor", "curly", "chill", "loped", "gooey", "boles", "genet", "boost", "beets", "heath",
                           "feeds", "growl", "livid", "midst", "rinds", "fresh", "waxed", "yearn", "keeps", "rimes",
                           "naked", "flick", "plies", "deeps", "dirty", "hefty", "messy", "hairy", "walks", "leper",
                           "sykes", "nerve", "rover", "jived", "brisk", "lenin", "viper", "chuck", "sinus", "luger",
                           "ricks", "hying", "rusty", "kathy", "herds", "wider", "getty", "roman", "sandy", "pends",
                           "fezes", "trios", "bites", "pants", "bless", "diced", "earth", "shack", "hinge", "melds",
                           "jonah", "chose", "liver", "salts", "ratty", "ashed", "wacky", "yokes", "wanly", "bruce",
                           "vowel", "black", "grail", "lungs", "arise", "gluts", "gluey", "navel", "coyer", "ramps",
                           "miter", "aldan", "booth", "musty", "rills", "darns", "tined", "straw", "kerri", "hared",
                           "lucks", "metes", "penny", "radon", "palms", "deeds", "earls", "shard", "pried", "tampa",
                           "blank", "gybes", "vicki", "drool", "groom", "curer", "cubes", "riggs", "lanky", "tuber",
                           "caves", "acing", "golly", "hodge", "beard", "ginny", "jibed", "fumes", "astor", "quito",
                           "cargo", "randi", "gawky", "zings", "blind", "dhoti", "sneak", "fatah", "fixer", "lapps",
                           "cline", "grimm", "fakes", "maine", "erika", "dealt", "mitch", "olden", "joist", "gents",
                           "likes", "shelf", "silts", "goats", "leads", "marin", "spire", "louie", "evans", "amuse",
                           "belly", "nails", "snead", "model", "whats", "shari", "quote", "tacks", "nutty", "lames",
                           "caste", "hexes", "cooks", "miner", "shawn", "anise", "drama", "trike", "prate", "ayers",
                           "loans", "botch", "vests", "cilia", "ridge", "thugs", "outed", "jails", "moped", "plead",
                           "tunes", "nosed", "wills", "lager", "lacks", "cried", "wince", "berle", "flaws", "boise",
                           "tibet", "bided", "shred", "cocky", "brice", "delta", "congo", "holly", "hicks", "wraps",
                           "cocks", "aisha", "heard", "cured", "sades", "horsy", "umped", "trice", "dorky", "curve",
                           "ferry", "haler", "ninth", "pasta", "jason", "honer", "kevin", "males", "fowls", "awake",
                           "pores", "meter", "skate", "drink", "pussy", "soups", "bases", "noyes", "torts", "bogus",
                           "still", "soupy", "dance", "worry", "eldon", "stern", "menes", "dolls", "dumpy", "gaunt",
                           "grove", "coops", "mules", "berry", "sower", "roams", "brawl", "greed", "stags", "blurs",
                           "swift", "treed", "taney", "shame", "easel", "moves", "leger", "ville", "order", "spock",
                           "nifty", "brian", "elias", "idler", "serve", "ashen", "bizet", "gilts", "spook", "eaten",
                           "pumas", "cotes", "broke", "toxin", "groan", "laths", "joins", "spots", "hated", "tokay",
                           "elite", "rawer", "fiats", "cards", "sassy", "milks", "roost", "glean", "lutes", "chins",
                           "drown", "marks", "pined", "grace", "fifth", "lodes", "rusts", "terms", "maxes", "savvy",
                           "choir", "savoy", "spoon", "halve", "chord", "hulas", "sarah", "celia", "deems", "ninny",
                           "wines", "boggy", "birch", "raved", "wales", "beams", "vibes", "riots", "warty", "nigel",
                           "askew", "faxes", "sedge", "sheol", "pucks", "cynic", "relax", "boers", "whims", "bents",
                           "candy", "luann", "slogs", "bonny", "barns", "iambs", "fused", "duffy", "guilt", "bruin",
                           "pawls", "penis", "poppy", "owing", "tribe", "tuner", "moray", "timid", "ceded", "geeks",
                           "kites", "curio", "puffy", "perot", "caddy", "peeve", "cause", "dills", "gavel", "manse",
                           "joker", "lynch", "crank", "golda", "waits", "wises", "hasty", "paves", "grown", "reedy",
                           "crypt", "tonne", "jerky", "axing", "swept", "posse", "rings", "staff", "tansy", "pared",
                           "glaze", "grebe", "gonna", "shark", "jumps", "vials", "unset", "hires", "tying", "lured",
                           "motes", "linen", "locks", "mamas", "nasty", "mamie", "clout", "nader", "velma", "abate",
                           "tight", "dales", "serer", "rives", "bales", "loamy", "warps", "plato", "hooch", "togae",
                           "damps", "ofter", "plumb", "fifes", "filmy", "wiper", "chess", "lousy", "sails", "brahe",
                           "ounce", "flits", "hindu", "manly", "beaux", "mimed", "liken", "forts", "jambs", "peeps",
                           "lelia", "brews", "handy", "lusty", "brads", "marne", "pesos", "earle", "arson", "scout",
                           "showy", "chile", "sumps", "hiked", "crook", "herbs", "silks", "alamo", "mores", "dunce",
                           "blaze", "stank", "haste", "howls", "trots", "creon", "lisle", "pause", "hates", "mulch",
                           "mined", "moder", "devin", "types", "cindy", "beech", "tuned", "mowed", "pitts", "chaos",
                           "colds", "bidet", "tines", "sighs", "slimy", "brain", "belle", "leery", "morse", "ruben",
                           "prows", "frown", "disco", "regal", "oaken", "sheds", "hives", "corny", "baser", "fated",
                           "throe", "revel", "bores", "waved", "shits", "elvia", "ferns", "maids", "color", "coifs",
                           "cohan", "draft", "hmong", "alton", "stine", "cluck", "nodes", "emily", "brave", "blair",
                           "blued", "dress", "bunts", "holst", "clogs", "rally", "knack", "demos", "brady", "blues",
                           "flash", "goofy", "blocs", "diane", "colic", "smile", "yules", "foamy", "splay", "bilge",
                           "faker", "foils", "condo", "knell", "crack", "gallo", "purls", "auras", "cakes", "doves",
                           "joust", "aides", "lades", "muggy", "tanks", "middy", "tarps", "slack", "capet", "frays",
                           "donny", "venal", "yeats", "misty", "denim", "glass", "nudes", "seeps", "gibbs", "blows",
                           "bobbi", "shane", "yards", "pimps", "clued", "quiet", "witch", "boxes", "prawn", "kerry",
                           "torah", "kinko", "dingy", "emote", "honor", "jelly", "grins", "trope", "vined", "bagel",
                           "arden", "rapid", "paged", "loved", "agape", "mural", "budge", "ticks", "suers", "wendi",
                           "slice", "salve", "robin", "bleat", "batik", "myles", "teddy", "flatt", "puppy", "gelid",
                           "largo", "attar", "polls", "glide", "serum", "fundy", "sucks", "shalt", "sewer", "wreak",
                           "dames", "fonts", "toxic", "hines", "wormy", "grass", "louse", "bowls", "crass", "benny",
                           "moire", "margo", "golfs", "smart", "roxie", "wight", "reign", "dairy", "clops", "paled",
                           "oddly", "sappy", "flair", "shown", "bulgy", "benet", "larch", "curry", "gulfs", "fends",
                           "lunch", "dukes", "doris", "spoke", "coins", "manna", "conga", "jinns", "eases", "dunno",
                           "tisha", "swore", "rhino", "calms", "irvin", "clans", "gully", "liege", "mains", "besot",
                           "serge", "being", "welch", "wombs", "draco", "lynda", "forty", "mumps", "bloch", "ogden",
                           "knits", "fussy", "alder", "danes", "loyal", "valet", "wooer", "quire", "liefs", "shana",
                           "toyed", "forks", "gages", "slims", "cloys", "yates", "rails", "sheep", "nacho", "divan",
                           "honks", "stone", "snack", "added", "basal", "hasps", "focus", "alone", "laxes", "arose",
                           "lamed", "wrapt", "frail", "clams", "plait", "hover", "tacos", "mooch", "fault", "teeth",
                           "marva", "mucks", "tread", "waves", "purim", "boron", "horde", "smack", "bongo", "monte",
                           "swirl", "deals", "mikes", "scold", "muter", "sties", "lawns", "fluke", "jilts", "meuse",
                           "fives", "sulky", "molds", "snore", "timmy", "ditty", "gasps", "kills", "carey", "jawed",
                           "byers", "tommy", "homer", "hexed", "dumas", "given", "mewls", "smelt", "weird", "speck",
                           "merck", "keats", "draws", "trent", "agave", "wells", "chews", "blabs", "roves", "grieg",
                           "evens", "alive", "mulls", "cared", "garbo", "fined", "happy", "trued", "rodes", "thurs",
                           "cadet", "alvin", "busch", "moths", "guild", "staci", "lever", "widen", "props", "hussy",
                           "lamer", "riley", "bauer", "chirp", "rants", "poxes", "shyer", "pelts", "funny", "slits",
                           "tinge", "ramos", "shift", "caper", "credo", "renal", "veils", "covey", "elmer", "mated",
                           "tykes", "wooed", "briar", "gears", "foley", "shoes", "decry", "hypes", "dells", "wilds",
                           "runts", "wilts", "white", "easts", "comer", "sammy", "lochs", "favor", "lance", "dawns",
                           "bushy", "muted", "elsie", "creel", "pocks", "tenet", "cagey", "rides", "socks", "ogled",
                           "soils", "sofas", "janna", "exile", "barks", "frank", "takes", "zooms", "hakes", "sagan",
                           "scull", "heaps", "augur", "pouch", "blare", "bulbs", "wryly", "homey", "tubas", "limbo",
                           "hardy", "hoagy", "minds", "bared", "gabby", "bilks", "float", "limns", "clasp", "laura",
                           "range", "brush", "tummy", "kilts", "cooed", "worms", "leary", "feats", "robes", "suite",
                           "veals", "bosch", "moans", "dozen", "rarer", "slyer", "cabin", "craze", "sweet", "talon",
                           "treat", "yanks", "react", "creed", "eliza", "sluts", "cruet", "hafts", "noise", "seder",
                           "flies", "weeks", "venus", "backs", "eider", "uriel", "vouch", "robed", "hacks", "perth",
                           "shiny", "stilt", "torte", "throb", "merer", "twits", "reeds", "shawl", "clara", "slurs",
                           "mixer", "newts", "fried", "woolf", "swoop", "kaaba", "oozed", "mayer", "caned", "laius",
                           "lunge", "chits", "kenny", "lifts", "mafia", "sowed", "piled", "stein", "whack", "colts",
                           "warms", "cleft", "girds", "seeks", "poets", "angel", "trade", "parsi", "tiers", "rojas",
                           "vexes", "bryce", "moots", "grunt", "drain", "lumpy", "stabs", "poohs", "leapt", "polly",
                           "cuffs", "giddy", "towns", "dacha", "quoth", "provo", "dilly", "carly", "mewed", "tzars",
                           "crock", "toked", "speak", "mayas", "pssts", "ocher", "motel", "vogue", "camps", "tharp",
                           "taunt", "drone", "taint", "badge", "scott", "scats", "bakes", "antes", "gruel", "snort",
                           "capes", "plate", "folly", "adobe", "yours", "papaw", "hench", "moods", "clunk", "chevy",
                           "tomas", "narcs", "vonda", "wiles", "prigs", "chock", "laser", "viced", "stiff", "rouse",
                           "helps", "knead", "gazer", "blade", "tumid", "avail", "anger", "egged", "guide", "goads",
                           "rabin", "toddy", "gulps", "flank", "brats", "pedal", "junky", "marco", "tinny", "tires",
                           "flier", "satin", "darth", "paley", "gumbo", "rared", "muffs", "rower", "prude", "frees",
                           "quays", "homes", "munch", "beefs", "leash", "aston", "colon", "finch", "bogey", "leaps",
                           "tempo", "posts", "lined", "gapes", "locus", "maori", "nixes", "liven", "songs", "opted",
                           "babel", "wader", "barer", "farts", "lisps", "koran", "lathe", "trill", "smirk", "mamma",
                           "viler", "scurf", "ravel", "brigs", "cooky", "sachs", "fulls", "goals", "turfs", "norse",
                           "hauls", "cores", "fairy", "pluto", "kneed", "cheek", "pangs", "risen", "czars", "milne",
                           "cribs", "genes", "wefts", "vents", "sages", "seres", "owens", "wiley", "flume", "haded",
                           "auger", "tatty", "onion", "cater", "wolfe", "magic", "bodes", "gulls", "gazes", "dandy",
                           "snags", "rowed", "quell", "spurn", "shore", "veldt", "turns", "slavs", "coach", "stalk",
                           "snuck", "piles", "orate", "joyed", "daily", "crone", "wager", "solos", "earns", "stark",
                           "lauds", "kasey", "villa", "gnaws", "scent", "wears", "fains", "laced", "tamer", "pipes",
                           "plant", "lorie", "rivet", "tamed", "cozen", "theme", "lifer", "sunny", "shags", "flack",
                           "gassy", "eased", "jeeps", "shire", "fargo", "timer", "brash", "behan", "basin", "volga",
                           "krone", "swiss", "docks", "booed", "ebert", "gusty", "delay", "oared", "grady", "buick",
                           "curbs", "crete", "lucas", "strum", "besom", "gorse", "troth", "donne", "chink", "faced",
                           "ahmed", "texas", "longs", "aloud", "bethe", "cacao", "hilda", "eagle", "karyn", "harks",
                           "adder", "verse", "drays", "cello", "taped", "snide", "taxis", "kinky", "penes", "wicca",
                           "sonja", "aways", "dyers", "bolas", "elfin", "slope", "lamps", "hutch", "lobed", "baaed",
                           "masts", "ashes", "ionic", "joyce", "payed", "brays", "malts", "dregs", "leaky", "runny",
                           "fecal", "woven", "hurls", "jorge", "henna", "dolby", "booty", "brett", "dykes", "rural",
                           "fight", "feels", "flogs", "brunt", "preen", "elvis", "dopey", "gripe", "garry", "gamma",
                           "fling", "space", "mange", "storm", "arron", "hairs", "rogue", "repel", "elgar", "ruddy",
                           "cross", "medan", "loses", "howdy", "foams", "piker", "halts", "jewel", "avery", "stool",
                           "cruel", "cases", "ruses", "cathy", "harem", "flour", "meted", "faces", "hobos", "charm",
                           "jamar", "cameo", "crape", "hooey", "reefs", "denny", "mitts", "sores", "smoky", "nopes",
                           "sooty", "twirl", "toads", "vader", "julep", "licks", "arias", "wrote", "north", "bunks",
                           "heady", "batch", "snaps", "claws", "fouls", "faded", "beans", "wimps", "idled", "pulse",
                           "goons", "noose", "vowed", "ronda", "rajas", "roast", "allah", "punic", "slows", "hours",
                           "metal", "slier", "meaty", "hanna", "curvy", "mussy", "truth", "troys", "block", "reels",
                           "print", "miffs", "busts", "bytes", "cream", "otter", "grads", "siren", "kilos", "dross",
                           "batty", "debts", "sully", "bares", "baggy", "hippy", "berth", "gorky", "argon", "wacko",
                           "harry", "smoke", "fails", "perms", "score", "steps", "unity", "couch", "kelly", "rumps",
                           "fines", "mouth", "broth", "knows", "becky", "quits", "lauri", "trust", "grows", "logos",
                           "apter", "burrs", "zincs", "buyer", "bayer", "moose", "overt", "croon", "ousts", "lands",
                           "lithe", "poach", "jamel", "waive", "wiser", "surly", "works", "paine", "medal", "glads",
                           "gybed", "paint", "lorre", "meant", "smugs", "bryon", "jinni", "sever", "viols", "flubs",
                           "melts", "heads", "peals", "aiken", "named", "teary", "yalta", "styes", "heist", "bongs",
                           "slops", "pouts", "grape", "belie", "cloak", "rocks", "scone", "lydia", "goofs", "rents",
                           "drive", "crony", "orlon", "narks", "plays", "blips", "pence", "march", "alger", "baste",
                           "acorn", "billy", "croce", "boone", "aaron", "slobs", "idyls", "irwin", "elves", "stoat",
                           "doing", "globe", "verve", "icons", "trial", "olsen", "pecks", "there", "blame", "tilde",
                           "milky", "sells", "tangy", "wrack", "fills", "lofty", "truce", "quark", "delia", "stowe",
                           "marty", "overs", "putty", "coral", "swine", "stats", "swags", "weans", "spout", "bulky",
                           "farsi", "brest", "gleam", "beaks", "coons", "hater", "peony", "huffy", "exert", "clips",
                           "riven", "payer", "doped", "salas", "meyer", "dryad", "thuds", "tilts", "quilt", "jetty",
                           "brood", "gulch", "corps", "tunic", "hubby", "slang", "wreck", "purrs", "punch", "drags",
                           "chide", "sulks", "tints", "huger", "roped", "dopes", "booby", "rosin", "outer", "gusto",
                           "tents", "elude", "brows", "lease", "ceres", "laxer", "worth", "necks", "races", "corey",
                           "trait", "stuns", "soles", "teems", "scrip", "privy", "sight", "minor", "alisa", "stray",
                           "spank", "cress", "nukes", "rises", "gusts", "aurae", "karma", "icing", "prose", "biked",
                           "grand", "grasp", "skein", "shaky", "clump", "rummy", "stock", "twain", "zoned", "offed",
                           "ghats", "mover", "randy", "vault", "craws", "thees", "salem", "downy", "sangs", "chore",
                           "cited", "grave", "spinx", "erica", "raspy", "dying", "skips", "clerk", "paste", "moved",
                           "rooks", "intel", "moses", "avers", "staid", "yawls", "blast", "lyres", "monks", "gaits",
                           "floor", "saner", "waver", "assam", "infer", "wands", "bunch", "dryly", "weedy", "honey",
                           "baths", "leach", "shorn", "shows", "dream", "value", "dooms", "spiro", "raped", "shook",
                           "stead", "moran", "ditto", "loots", "tapir", "looms", "clove", "stops", "pinks", "soppy",
                           "ripen", "wench", "shone", "bauds", "doric", "leans", "nadia", "cries", "camus", "boozy",
                           "maris", "fools", "morns", "bides", "greek", "gauss", "roget", "lamar", "hazes", "beefy",
                           "dupes", "refed", "felts", "larry", "guile", "ables", "wants", "warns", "toils", "bathe",
                           "edger", "paced", "rinks", "shoos", "erich", "whore", "tiger", "jumpy", "lamas", "stack",
                           "among", "punts", "scalp", "alloy", "solon", "quite", "comas", "whole", "parse", "tries",
                           "reeve", "tiled", "deena", "roomy", "rodin", "aster", "twice", "musts", "globs", "parch",
                           "drawn", "filch", "bonds", "tells", "droop", "janis", "holds", "scant", "lopes", "based",
                           "keven", "whiny", "aspic", "gains", "franz", "jerri", "steel", "rowel", "vends", "yelps",
                           "begin", "logic", "tress", "sunni", "going", "barge", "blood", "burns", "basks", "waifs",
                           "bones", "skill", "hewer", "burly", "clime", "eking", "withs", "capek", "berta", "cheap",
                           "films", "scoot", "tweed", "sizer", "wheat", "acton", "flung", "ponds", "tracy", "fiver",
                           "berra", "roger", "mutes", "burke", "miked", "valve", "whisk", "runes", "parry", "toots",
                           "japes", "roars", "rough", "irons", "romeo", "cages", "reeks", "cigar", "saiph", "dully",
                           "hangs", "chops", "rolls", "prick", "acuff", "spent", "sulla", "train", "swell", "frets",
                           "names", "anita", "crazy", "sixth", "blunt", "fewer", "large", "brand", "slick", "spitz",
                           "rears", "ogres", "toffy", "yolks", "flock", "gnawn", "eries", "blink", "skier", "feted",
                           "tones", "snail", "ether", "barbs", "noses", "hears", "upset", "awash", "cloud", "trunk",
                           "degas", "dungs", "rated", "shall", "yeahs", "coven", "sands", "susan", "fable", "gunny",
                           "began", "serfs", "balls", "dinky", "madge", "prong", "spilt", "lilly", "brawn", "comet",
                           "spins", "raids", "dries", "sorts", "makes", "mason", "mayra", "royce", "stout", "mealy",
                           "pagan", "nasal", "folds", "libby", "coups", "photo", "mosey", "amens", "speed", "lords",
                           "board", "fetal", "lagos", "scope", "raked", "bonus", "mutts", "willy", "sport", "bingo",
                           "thant", "araby", "bette", "rebel", "gases", "small", "humus", "grosz", "beset", "slays",
                           "steve", "scrap", "blahs", "south", "pride", "heels", "tubes", "beady", "lacey", "genus",
                           "mauls", "vying", "spice", "sexes", "ester", "drams", "today", "comae", "under", "jests",
                           "direr", "yoked", "tempi", "early", "boats", "jesus", "warts", "guppy", "gilda", "quota",
                           "token", "edwin", "ringo", "gaped", "lemon", "hurst", "manor", "arrow", "mists", "prize",
                           "silas", "blobs", "diets", "ervin", "stony", "buddy", "bates", "rabid", "ducat", "ewing",
                           "jaunt", "beads", "doyen", "blush", "thoth", "tiles", "piper", "short", "peron", "alley",
                           "decks", "shunt", "whirs", "cushy", "roils", "betty", "plugs", "woken", "jibes", "foray",
                           "merak", "ruing", "becks", "whale", "shoot", "dwelt", "spawn", "fairs", "dozed", "celts",
                           "blond", "tikes", "sabin", "feint", "vamps", "cokes", "willa", "slues", "bills", "force",
                           "curst", "yokel", "surer", "miler", "fices", "arced", "douse", "hilly", "lucio", "tongs",
                           "togas", "minty", "sagas", "pates", "welsh", "bruno", "decal", "elate", "linux", "gyros",
                           "pryor", "mousy", "pains", "shake", "spica", "pupal", "probe", "mount", "shirk", "purus",
                           "kilns", "rests", "graze", "hague", "spuds", "sweep", "momma", "burch", "maces", "samar",
                           "brace", "riser", "booms", "build", "camel", "flyer", "synge", "sauna", "tonga", "tings",
                           "promo", "hides", "clair", "elisa", "bower", "reins", "diann", "lubed", "nulls", "picks",
                           "laban", "milch", "buber", "stomp", "bosom", "lying", "haled", "avert", "wries", "macon",
                           "skids", "fumed", "ogles", "clods", "antic", "nosey", "crimp", "purge", "mommy", "cased",
                           "taxes", "covet", "clack", "butch", "panty", "lents", "machs", "exude", "tooth", "adore",
                           "shuck", "asses", "after", "terra", "dices", "aryan", "regor", "romes", "stile", "cairo",
                           "maura", "flail", "eaves", "estes", "sousa", "visas", "baron", "civet", "kitty", "freed",
                           "ralph", "tango", "gawks", "cheat", "study", "fancy", "fiber", "musks", "souse", "brims",
                           "claim", "bikes", "venue", "sired", "thymi", "rivas", "skimp", "pleas", "woman", "gimpy",
                           "cawed", "minos", "pints", "knock", "poked", "bowen", "risky", "towel", "oinks", "linus",
                           "heals", "pears", "codas", "inner", "pitch", "harpy", "niger", "madly", "bumpy", "stair",
                           "files", "nobel", "celli", "spars", "jades", "balmy", "kooky", "plums", "trues", "gloss",
                           "trims", "daunt", "tubby", "dared", "wadis", "smell", "darby", "stink", "drill", "dover",
                           "ruler", "laden", "dikes", "layla", "fells", "maker", "joked", "horns", "these", "baize",
                           "spahn", "whens", "edged", "mushy", "plume", "tucks", "spurs", "husky", "dried", "bigot",
                           "pupas", "drily", "aware", "hagar", "newly", "knots", "pratt", "feces", "sabik", "watts",
                           "cooke", "riles", "seamy", "fleas", "dusts", "barfs", "roans", "pawns", "vivid", "kirks",
                           "tania", "feral", "tubae", "horne", "aries", "brits", "combs", "chunk", "stork", "waned",
                           "texan", "elide", "glens", "emery", "autos", "trams", "dosed", "cheri", "baits", "jacks",
                           "whose", "fazed", "matte", "swans", "maxed", "write", "spays", "orion", "traci", "horse",
                           "stars", "strut", "goods", "verge", "scuff", "award", "dives", "wires", "burnt", "dimly",
                           "sleds", "mayan", "biped", "quirk", "sofia", "slabs", "waste", "robby", "mayor", "fatty",
                           "items", "bowel", "mires", "swarm", "route", "swash", "sooth", "paved", "steak", "upend",
                           "sough", "throw", "perts", "stave", "carry", "burgs", "hilts", "plane", "toady", "nadir",
                           "stick", "foist", "gnarl", "spain", "enter", "sises", "story", "scarf", "ryder", "glums",
                           "nappy", "sixes", "honed", "marcy", "offer", "kneel", "leeds", "lites", "voter", "vince",
                           "bursa", "heave", "roses", "trees", "argos", "leann", "grimy", "zelma", "crick", "tract",
                           "flips", "folks", "smote", "brier", "moore", "goose", "baden", "riled", "looks", "sober",
                           "tusks", "house", "acmes", "lubes", "chows", "neath", "vivas", "defer", "allay", "casey",
                           "kmart", "pests", "proms", "eying", "cider", "leave", "shush", "shots", "karla", "scorn",
                           "gifts", "sneer", "mercy", "copes", "faxed", "spurt", "monet", "awoke", "rocky", "share",
                           "gores", "drawl", "tears", "mooed", "nones", "wined", "wrens", "modem", "beria", "hovel",
                           "retch", "mates", "hands", "stymy", "peace", "carat", "coots", "hotel", "karen", "hayed",
                           "mamet", "cuing", "paper", "rages", "suave", "reuse", "auden", "costs", "loner", "rapes",
                           "hazel", "rites", "brent", "pumps", "dutch", "puffs", "noons", "grams", "teats", "cease",
                           "honda", "pricy", "forgo", "fleck", "hired", "silos", "merge", "rafts", "halon", "larks",
                           "deere", "jello", "cunts", "sifts", "boner", "morin", "mimes", "bungs", "marie", "harts",
                           "snobs", "sonic", "hippo", "comes", "crops", "mango", "wrung", "garbs", "natty", "cents",
                           "fitch", "moldy", "adams", "sorta", "coeds", "gilds", "kiddy", "nervy", "slurp", "ramon",
                           "fuzed", "hiker", "winks", "vanes", "goody", "hawks", "crowd", "bract", "marla", "limbs",
                           "solve", "gloom", "sloop", "eaton", "memos", "tames", "heirs", "berms", "wanes", "faint",
                           "numbs", "holes", "grubs", "rakes", "waist", "miser", "stays", "antis", "marsh", "skyed",
                           "payne", "champ", "jimmy", "clues", "fatal", "shoed", "freon", "lopez", "snowy", "loins",
                           "stale", "thank", "reads", "isles", "grill", "align", "saxes", "rubin", "rigel", "walls",
                           "beers", "wispy", "topic", "alden", "anton", "ducts", "david", "duets", "fries", "oiled",
                           "waken", "allot", "swats", "woozy", "tuxes", "inter", "dunne", "known", "axles", "graph",
                           "bumps", "jerry", "hitch", "crews", "lucia", "banal", "grope", "valid", "meres", "thick",
                           "lofts", "chaff", "taker", "glues", "snubs", "trawl", "keels", "liker", "stand", "harps",
                           "casks", "nelly", "debby", "panes", "dumps", "norma", "racks", "scams", "forte", "dwell",
                           "dudes", "hypos", "sissy", "swamp", "faust", "slake", "maven", "lowed", "lilts", "bobby",
                           "gorey", "swear", "nests", "marci", "palsy", "siege", "oozes", "rates", "stunt", "herod",
                           "wilma", "other", "girts", "conic", "goner", "peppy", "class", "sized", "games", "snell",
                           "newsy", "amend", "solis", "duane", "troop", "linda", "tails", "woofs", "scuds", "shies",
                           "patti", "stunk", "acres", "tevet", "allen", "carpi", "meets", "trend", "salty", "galls",
                           "crept", "toner", "panda", "cohen", "chase", "james", "bravo", "styed", "coals", "oates",
                           "swami", "staph", "frisk", "cares", "cords", "stems", "razed", "since", "mopes", "rices",
                           "junes", "raged", "liter", "manes", "rearm", "naive", "tyree", "medic", "laded", "pearl",
                           "inset", "graft", "chair", "votes", "saver", "cains", "knobs", "gamay", "hunch", "crags",
                           "olson", "teams", "surge", "wests", "boney", "limos", "ploys", "algae", "gaols", "caked",
                           "molts", "glops", "tarot", "wheal", "cysts", "husks", "vaunt", "beaus", "fauns", "jeers",
                           "mitty", "stuff", "shape", "sears", "buffy", "maced", "fazes", "vegas", "stamp", "borer",
                           "gaged", "shade", "finds", "frock", "plods", "skied", "stump", "ripes", "chick", "cones",
                           "fixed", "coled", "rodeo", "basil", "dazes", "sting", "surfs", "mindy", "creak", "swung",
                           "cadge", "franc", "seven", "sices", "weest", "unite", "codex", "trick", "fusty", "plaid",
                           "hills", "truck", "spiel", "sleek", "anons", "pupae", "chiba", "hoops", "trash", "noted",
                           "boris", "dough", "shirt", "cowls", "seine", "spool", "miens", "yummy", "grade", "proxy",
                           "hopes", "girth", "deter", "dowry", "aorta", "paean", "corms", "giant", "shank", "where",
                           "means", "years", "vegan", "derek", "tales"};
    vector<string> ans = {"hot", "dot", "dog", "lot", "log", "cog"};
    cout << s.ladderLength("hit", "cog", ans);
}
