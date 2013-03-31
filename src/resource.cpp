//30.03.2013
//v0.1

#include "resource.hpp"
#include <wx/intl.h> 

Resource::Resource()
{
	//Liste des langues
	_langs["af"] = _("Afrikaans");
	_langs["sq"] = _("Albanian");
	_langs["ar"] = _("Arabic");
	_langs["hy"] = _("Armenian");
	_langs["az"] = _("Azerbaijani");
	_langs["eu"] = _("Basque");
	_langs["be"] = _("Belarusian");
	_langs["bn"] = _("Bengali");
	_langs["bg"] = _("Bulgarian");
	_langs["ca"] = _("Catalan");
	_langs["zh-CN"] = _("Chinese");
	_langs["hr"] = _("Croatian");
	_langs["sr"] = _("Czech");
	_langs["da"] = _("Danish");
	_langs["nl"] = _("Dutch");
	_langs["en"] = _("English");
	_langs["eo"] = _("Esperanto");
	_langs["et"] = _("Estonian");
	_langs["tl"] = _("Filipino");
	_langs["fi"] = _("Finnish");
	_langs["fr"] = _("French");
	_langs["gl"] = _("Galician");
	_langs["ka"] = _("Georgian");
	_langs["de"] = _("German");
	_langs["el"] = _("Greek");
	_langs["gu"] = _("Gujarati");
	_langs["ht"] = _("Haitian Creole");
	_langs["iw"] = _("Hebrew");
	_langs["hi"] = _("Hindi");
	_langs["hu"] = _("Hungarian");
	_langs["is"] = _("Icelandic");
	_langs["id"] = _("Indonesian");
	_langs["ga"] = _("Irish");
	_langs["it"] = _("Italian");
	_langs["ja"] = _("Japanese");
	_langs["kn"] = _("Kannada");
	_langs["ko"] = _("Korean");
	_langs["lo"] = _("Lao");
	_langs["la"] = _("Latin");
	_langs["lv"] = _("Latvian");
	_langs["it"] = _("Lithuanian");
	_langs["mk"] = _("Macedonian");
	_langs["ms"] = _("Malay");
	_langs["mt"] = _("Maltese");
	_langs["no"] = _("Norwegian");
	_langs["fa"] = _("Persian");
	_langs["pl"] = _("Polish");
	_langs["pt"] = _("Portuguese");
	_langs["ro"] = _("Romanian");
	_langs["ru"] = _("Russian");
	_langs["sr"] = _("Serbian");
	_langs["sk"] = _("Slovak");
	_langs["sl"] = _("Slovenian");
	_langs["es"] = _("Spanish");
	_langs["sw"] = _("Swahili");
	_langs["sv"] = _("Swedish");
	_langs["ta"] = _("Tamil");
	_langs["te"] = _("Telugu");
	_langs["th"] = _("Thai");
	_langs["tr"] = _("Turkish");
	_langs["uk"] = _("Ukrainian");
	_langs["ur"] = _("Urdu");
	_langs["vi"] = _("Vietnamese");
	_langs["cy"] = _("Welsh");
	_langs["yi"] = _("Yiddish");
	
	
	//Liste des actions
	#ifdef USE_ACT_TRANSLATION
	_actions.push_back(_("Translation"));
	#endif
	#ifdef USE_ACT_SAVE_TRANSLATION
	_actions.push_back(_("Save translation"));
	#endif
	#ifdef USE_ACT_SAY
	_actions.push_back(_("Say"));
	#endif
}

Resource::~Resource()
{
}

std::map<wxString, wxString> const& Resource::getLangs()
{
	return _langs;
}

std::vector<wxString> const& Resource::getActions()
{
	return _actions;
}
