/*******************************************************************************
 *
 * Copyright (C) 2009, Alexander Stigsen, e-texteditor.com
 *
 * This software is licensed under the Open Company License as described
 * in the file license.txt, which you should have received as part of this
 * distribution. The terms are also available at http://opencompany.org/license.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ******************************************************************************/

#ifndef __STYLER_VARIABLEHL_H__
#define __STYLER_VARIABLEHL_H__

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
	#include <wx/string.h>
	#include <wx/colour.h>
#endif

#include "Catalyst.h"
#include "styler.h"
#include "eSettings.h"

#include <vector>


class DocumentWrapper;
class StyleRun;
struct tmTheme;
class Lines;

class Styler_VariableHL : public Styler {
public:
	Styler_VariableHL(const DocumentWrapper& rev, const Lines& lines, const std::vector<interval>& ranges, const tmTheme& theme, eSettings& settings);
	virtual ~Styler_VariableHL() {};

	void Clear();
	void Invalidate();
	void SetCurrentWord(const wxString& text, bool click, unsigned int cursosPosition, int key);
	void Style(StyleRun& sr);

	bool ShouldStyle();
	int GetStyleType(unsigned int start, unsigned int end);
	bool IsCurrentWord(unsigned int start, unsigned int end);
	bool IsArrowKey(int key);

	// Handle document changes
	void Insert(unsigned int pos, unsigned int length);
	void Delete(unsigned int start_pos, unsigned int end_pos);
	void ApplyDiff(const std::vector<cxChange>& changes);

private:
	void DoSearch(unsigned int start, unsigned int end, bool from_last=false);

	// Member variables
	const DocumentWrapper& m_doc;
	const Lines& m_lines;
	wxString m_text;
	std::vector<interval> m_matches;
	eSettings& m_settings;

	bool m_click;
	unsigned int m_cursorPosition;
	int m_key;

	// Theme variables
	const tmTheme& m_theme;
	const wxColour& m_searchHighlightColor;
	const wxColour& m_selectionHighlightColor;

	unsigned int m_search_start;
	unsigned int m_search_end;
	static const unsigned int EXTSIZE;
};

#endif // __STYLER_VARIABLEHL_H__
