#ifndef I18N_H
#define I18N_H

#include <locale.h>
#include <string.h>
#include <strings.h>

// Minimal i18n: T(key) returns the current language string for key,
// falling back to English if not found or no translation set.

// Languages: "en" (default, returns key itself), "zh", "ja", etc.
// Stored as raw UTF-8.

extern const char *g_i18n_lang;

const char *T(const char *key);
void          i18n_init(void);
void          i18n_set_lang(const char *lang);
const char *  i18n_get_lang(void);
bool          i18n_is_cjk(void);

#endif // I18N_H
