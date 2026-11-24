#include "../i18n.h"

#include <stdio.h>
#include <string.h>

static int failures;
static int checks;

static void check(bool condition, const char *description) {
	checks++;
	if (!condition) {
		failures++;
		fprintf(stderr, "FAIL: %s\n", description);
	}
}

static void check_equal(const char *actual, const char *expected, const char *description) {
	checks++;
	if (0 != strcmp(actual, expected)) {
		failures++;
		fprintf(stderr, "FAIL: %s (got '%s', expected '%s')\n", description, actual, expected);
	}
}

int main() {
	// Default English fallback.
	i18n_set_lang("en");
	check_equal(T("Run"), "Run", "English returns the key");
	check_equal(T("Run\tShift+F5"), "Run\tShift+F5", "English returns key with shortcut");
	check_equal(T("unknown-key"), "unknown-key", "Unknown keys return themselves");

	// Simplified Chinese, exact entries.
	i18n_set_lang("zh_CN.UTF-8");
	check_equal(i18n_get_lang(), "zh", "zh_CN normalizes to zh");
	check(i18n_is_cjk(), "zh is CJK");
	check_equal(T("Run"), "运行", "Chinese Run");
	check_equal(T("OK"), "确定", "Chinese OK");
	check_equal(T("Language..."), "语言...", "Chinese language menu");

	// Prefix matching: translated base plus runtime suffix.
	check_equal(T("Run\tShift+F5"), "运行\tShift+F5", "Chinese shortcut suffix preserved");
	check_equal(T("Continue\tF5"), "继续\tF5", "Chinese continue shortcut");
	check_equal(T("Couldn't get the working directory.\n%f%B"),
			"无法获取工作目录。\n%f%B", "Chinese dialog format markers preserved");

	// Traditional Chinese is distinct from Simplified.
	i18n_set_lang("zh_TW.UTF-8");
	check_equal(i18n_get_lang(), "zh-hant", "zh_TW keeps hant script");

	// Japanese.
	i18n_set_lang("ja_JP.UTF-8");
	check_equal(i18n_get_lang(), "ja", "ja_JP normalizes to ja");
	check(i18n_is_cjk(), "ja is CJK");
	check_equal(T("Run"), "実行", "Japanese Run");
	check_equal(T("Language..."), "言語...", "Japanese language menu");

	// English is not CJK.
	i18n_set_lang("en_US.UTF-8");
	check(!i18n_is_cjk(), "en is not CJK");

	// Null key is safe.
	check_equal(T(nullptr), "", "Null key returns empty string");

	printf("i18n: %d checks, %d failures\n", checks, failures);
	return failures ? 1 : 0;
}
