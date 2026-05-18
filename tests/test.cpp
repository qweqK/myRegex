#include "DFA/DFA.h"
#include "DFA/DFAconstruct.h"
#include  "DFA/MultiDFA.h"
#include  "regex/mregex.h"
#include "tree/tree.h"
#include  "tree/treeContructor.h"
#include <catch2/catch.hpp>


TEST_CASE("test ez operations") {
    SECTION("or r1|r2") {
        mregex m("a|b");
        REQUIRE(m.match("a"));
        REQUIRE(m.match("b"));
        REQUIRE(!m.match("c"));
    }
    SECTION("con .") {
        mregex m("a.b");
        REQUIRE(m.match("ab"));
        REQUIRE(!m.match("ba"));
    }
    SECTION("con ") {
        mregex m("ab");
        REQUIRE(m.match("ab"));
        REQUIRE(!m.match("ba"));
    }
    SECTION("Kleene star *") {
        mregex m("a*");
        REQUIRE(m.match("a"));
        REQUIRE(m.match("aaaaaaaaaaaaaaaaaaaaaaa"));
        REQUIRE(m.match(""));
        REQUIRE(!m.match("b"));

    }
    SECTION("positive +") {
        mregex m("a+");
        REQUIRE(m.match("a"));
        REQUIRE(m.match("aaaaaaaaaaaaaaaaaaaaaaa"));
        REQUIRE(!m.match(""));
        REQUIRE(!m.match("b"));
    }
    SECTION("empty") {
        mregex m("");
        REQUIRE(m.match(""));
        REQUIRE(!m.match("a"));
    }
}
    TEST_CASE("range []") {
        SECTION("Start from a-z") {
            mregex m("[a-z][a-z]");
            REQUIRE(m.match("az"));
            REQUIRE(!m.match("azg"));
        }
        SECTION("Start from a-z and solo symbol") {
            mregex m2("[a-z0-9 ]*");
            REQUIRE(m2.match("qweqwewqswfq2321     1232 1232sq23"));
            REQUIRE(!m2.match("qweqwewqswfq2321     12A2 1232sq23"));
        }
        SECTION("Start from solo symbol and a-z") {
            mregex m3("[ aqwe1hA-Z]*");
            REQUIRE(m3.match("  1hawew"));
            REQUIRE(m3.match("  1hAwEw"));
            REQUIRE(!m3.match("  1hawewz"));
        }
        SECTION("wrong") {
            CHECK_THROWS(mregex("[z-a]"));
        }

    }

    TEST_CASE("range {}") {

    SECTION("second limit empty") {
        mregex m("a{1,}");
        REQUIRE(m.match("a"));
        REQUIRE(!m.match(""));
        REQUIRE(!m.match("b"));
        REQUIRE(m.match("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    }
    SECTION("first limit empty") {
        mregex m("a{,3}");
        REQUIRE(m.match(""));
        REQUIRE(m.match("a"));
        REQUIRE(m.match("aaa"));
        REQUIRE(!m.match("aaaa"));
    }
    SECTION("first > second") {
       CHECK_THROWS(mregex("a{3,2}"));
    }
    SECTION("normally") {
        mregex m("a{1,5}");
        REQUIRE(m.match("a"));
        REQUIRE(!m.match(""));
        REQUIRE(m.match("aaa"));
        REQUIRE(m.match("aaaaa"));
        REQUIRE(!m.match("aaaaaa"));
        REQUIRE(!m.match("b"));
    }
}



    TEST_CASE("lookahead") {
    mregex m("abc/a");
    REQUIRE(m.match("abca"));
    REQUIRE(!m.match("abc"));
    REQUIRE(!m.match("abcc"));

    mregex m2("a+/a");
    REQUIRE(!m2.match("a"));
    REQUIRE(m2.match("aaaaaa"));
    REQUIRE(m2.match("aa"));
    mregex m3("a+/a+");

    REQUIRE(!m3.match("a"));
    REQUIRE(m3.match("aaaaaa"));
    REQUIRE(m3.match("aa"));

    mregex m4("uo(qw|eq)*/com");
    REQUIRE(m4.match("uoqweqeqqwcom"));
    REQUIRE(!m4.match("uoqwco"));
}

    TEST_CASE("isEaualLanguage") {
     SECTION("ez") {
         mregex m("abc");
         mregex m2("abc");
         REQUIRE(m.isEqual(m2));
         mregex m3("abbc");
         REQUIRE(!m3.isEqual(m2));
         mregex m4("a+");
         mregex m5("aa*");
         REQUIRE(m4.isEqual(m5));
     }
     SECTION("some harder") {
        mregex m("a*spasite");
         mregex m2("a+spasite");
         REQUIRE(!m2.isEqual(m));
     }
    SECTION("d") {
         mregex m("a|b|c");
         mregex m2 ("a|b|c|d");
         REQUIRE(!m.isEqual(m2));
     }
}

    TEST_CASE("k-Path recovery") {
    SECTION("ez") {
        mregex m("abc");
        mregex m2(m.kPath());
        REQUIRE(m.isEqual(m2));
        mregex m3("(abc*abac)+");
        mregex m4(m3.kPath());
        REQUIRE(m3.isEqual(m4));
    }
    SECTION("some harder") {
        mregex m("([a-zA-Z]+)( +-[a-zA-Z]+)*( +[a-zA-Z]+)* *");
        mregex m2(m.kPath());
        mregex m3(m.kPath()+ "q");
        REQUIRE(m.isEqual(m2));
        REQUIRE(!m.isEqual(m3));
    }
    SECTION("") {
        mregex m("");
        mregex m2(m.kPath());
        REQUIRE(m2.isEqual(m));
    }
    SECTION("diap+k-Path") {
        mregex m("[a-bA-B]*polo{3,4}");
        mregex m2(m.kPath());
        REQUIRE(m2.isEqual(m));
    }
}

TEST_CASE("invers yaz") {
    SECTION("ez") {
        mregex m("qwe");
        std::string f = m.invers();
        mregex m2(f);
        mregex m3("ewq");
        REQUIRE(m2.isEqual(m3));
        mregex m4("L(L|D)*");
        mregex m5(m4.invers());
        mregex m6("(L|D)*L");
        REQUIRE(m5.isEqual(m6));
        REQUIRE(m2.match("ewq"));
        REQUIRE(m5.match("DDLDLLDLDDLLDDLLDDLLLLDLDLDLLDLDL"));
        REQUIRE(!m5.match("DDLDLLDLDDLLDDLLDDLLLLDLDLDLLDLD"));
    }
    SECTION("oda") {
        mregex m("([a-zA-Z]+)( +-[a-zA-Z]+)*( +[a-zA-Z]+)* *");
        mregex m2(m.invers());
        mregex m3(" *([a-zA-Z]+ +)*([a-zA-Z]+- +)*([a-zA-Z]+)");
        REQUIRE(m2.isEqual(m3));
    }
    SECTION("empty") {
        mregex m("");
        mregex m2(m.invers());
        mregex m3("");
        REQUIRE(m2.isEqual(m3));
    }
}

TEST_CASE("difference jazikov") {
    SECTION("waf") {
        mregex m("a(a|b)*");
        mregex m2("(a|b)*b");
        mregex m3(m.diffAutomat(m2));
        mregex m4("a(a|b)*a|a");
        REQUIRE(m4.isEqual(m3));
    }
    SECTION("afff") {
        mregex m("a*");
        mregex m2("aaa*");
        mregex m3(m.diffAutomat(m2));
        mregex m4("a|$");
        REQUIRE(m4.isEqual(m3));
    }
    SECTION("empty") {
        mregex m("a|b");
        mregex m2("a|b");
        mregex m3(m.diffAutomat(m2));
        REQUIRE_THROWS(m3.kPath());
    }
    SECTION("s") {
        mregex m("a*a");
        mregex m2("");
        mregex m3(m.diffAutomat(m2));
        REQUIRE(m3.isEqual(m));
    }
    SECTION("[a-zA-Z]") {
        mregex m("[a-zA-Z]");
        mregex m2("[d-zD-Z]");
        mregex m3(m.diffAutomat(m2));
        mregex m4("[a-cA-C]");
        REQUIRE(m4.isEqual(m3));
    }
    SECTION("f") {
        mregex m("a*");
        mregex m2("");
        mregex m3(m.diffAutomat(m2));
        mregex m4("a+");
        REQUIRE(m4.isEqual(m3));
    }
    SECTION("prekol") {
        mregex m("[mephi]{5,5}");
        REQUIRE(m.match("mephi"));
        mregex m2("mephi");
        mregex m3(m.diffAutomat(m2));
        REQUIRE(!m3.match("mephi"));
        REQUIRE(m.match("mephe"));
        REQUIRE(m.match("mephh"));
        REQUIRE(!m.match("meph"));
    }
    SECTION("dif=empti") {
        mregex m("a|b|c");
        mregex m2("a|b|c");
        mregex m3(m.diffAutomat(m2));
        mregex m4("g|a|b");
        mregex m5(m4.diffAutomat(m3));
        REQUIRE(m5.isEqual(m4));
    }


}

TEST_CASE("combanations") {
    SECTION("regex from my first lab") {
        mregex m("([a-zA-Z]+)( +-[a-zA-Z]+)*( +[a-zA-Z]+)* *");
        REQUIRE(m.match("qwqeqw"));
        REQUIRE(m.match("qwqeqw -qwefqw"));
        REQUIRE(m.match("qwqeqw -qwegqw erwegwd"));
        REQUIRE(!m.match("qwqeqw -qwegqw erwegwd -dzbb"));
    }
    SECTION("{}+") {
        mregex m("(Mep*hi){3,5}");
        REQUIRE(m.match("MepppppppppphiMepphiMehiMephi"));
        REQUIRE(!m.match("MepppppppppphiMepphi"));
    }
    SECTION("niauu") {
        mregex m("n{3,}yau{2,}");
        REQUIRE(m.match("nnnnnyauuu"));
    }
    SECTION("da.ru") {
        mregex m("https:%/%/[a-z]{6,20}(%.[a-z]{2,5})*%.ru");
        REQUIRE(m.match("https://pomogite.mne.ya.ustal.ru"));
        REQUIRE(!m.match("https://pom.mne.ya.ustal.ru"));
    }
}

TEST_CASE("capture") {
    SECTION("easy") {
        mregex m("(aaa)(ooo)");
        msmatch msm;
        REQUIRE(m.match("aaaooo", msm));
        REQUIRE(msm[0] == "aaaooo");
        REQUIRE(msm[1] == "aaa");
        REQUIRE(msm[2] == "ooo");
        REQUIRE(!m.match("aaaoooo", msm));
    }
    SECTION("a*a*") {
        mregex m("(a*)(a*)");
        msmatch msm;
        REQUIRE(m.match("aaaaa", msm));
        REQUIRE(msm[0] == "aaaaa");
        REQUIRE(msm[1] == "aaaaa");
        REQUIRE(msm[2] == "");
    }
    SECTION("a+a+") {
        mregex m("(a+)(a+)");
        msmatch msm;
        REQUIRE(m.match("aaaaa", msm));
        REQUIRE(msm[0] == "aaaaa");
        REQUIRE(msm[1] == "aaaa");
        REQUIRE(msm[2] == "a");
    }
    SECTION("vetvleniye") {
        mregex m("(a*)(a*)|(a*)");
        msmatch msm;
        REQUIRE(m.match("aaaaa", msm));
        REQUIRE(msm[0] == "aaaaa");
        REQUIRE(msm[1] == "aaaaa");
        REQUIRE(msm[2] == "");
        REQUIRE(msm[3] == "");
    }
    SECTION("vetvleniye2") {
        mregex m("(a*)(a*)|((a*)b)");
        msmatch msm;
        REQUIRE(m.match("aaaaab", msm));
        REQUIRE(msm[0] == "aaaaab");
        REQUIRE(msm[1] == "");
        REQUIRE(msm[2] == "");
        REQUIRE(msm[3] == "aaaaab");
        REQUIRE(msm[4] == "aaaaa");
    }

}





