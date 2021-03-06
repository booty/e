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

#ifndef __THEMEEDITOR_H__
#define __THEMEEDITOR_H__

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "plistHandler.h"

#include <vector>

class ITmThemeHandler;

class wxGrid;
class wxGridEvent;
class wxGridRangeSelectEvent;

class ThemeEditor : public wxDialog {
public:
	ThemeEditor(wxWindow *parent, ITmThemeHandler& syntaxHandler);
	~ThemeEditor();

	void OnSelectorKillFocus(); // called by selectorCtrl

private:
	void Clear();
	void SetTheme(const PListHandler::cxItemRef& themeRef, bool init=false);
	void SizeGrid();
	void EnableCtrls();

	void SetSettingColour(unsigned int ndx, const char* id, const wxColour& colour, unsigned int alpha);
	void SetSettingFontStyle(unsigned int ndx, bool bold, bool italic, bool underline);
	void SetSelectorValue(unsigned int ndx, const char* key, const wxString& value, bool reloadTheme=false);

	bool AskForColour(wxColour& colour, unsigned int& alpha);
	void NotifyThemeChanged();

	void SetColour(const wxColour& colour, const unsigned int alpha, const int row, const int col);

	// Event handlers
	void OnFontSelect(wxCommandEvent& event);
	void OnFontQuality(wxCommandEvent& event);
	void OnThemeSelected(wxCommandEvent& event);
	void OnNewTheme(wxCommandEvent& event);
	void OnDelTheme(wxCommandEvent& event);
	void OnButtonFg(wxCommandEvent& event);
	void OnButtonBg(wxCommandEvent& event);
	void OnButtonSel(wxCommandEvent& event);
	void OnButtonInv(wxCommandEvent& event);
	void OnButtonLine(wxCommandEvent& event);
	//void OnButtonCaret(wxCommandEvent& event);
	void OnButtonSearchHL(wxCommandEvent& event);
	void OnButtonBracketHL(wxCommandEvent& event);
	void OnButtonGutter(wxCommandEvent& event);
	void OnButtonMulti(wxCommandEvent& event);
	void OnNewSetting(wxCommandEvent& event);
	void OnDelSetting(wxCommandEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnGridSelect(wxGridEvent& event);
	void OnGridSelectRange(wxGridRangeSelectEvent& event);
	void OnGridLeftDClick(wxGridEvent& event);
	void OnGridCellChange(wxGridEvent& event);
	void OnGridRightClick(wxGridEvent& event);
	void OnCopyColour(wxCommandEvent& event);
	void OnPasteColour(wxCommandEvent& event);
	DECLARE_EVENT_TABLE();

	class ColourButton : public wxBitmapButton {
	public:
		ColourButton(wxWindow* parent, wxWindowID id);
		void Clear();
		void SetColour(const wxColour& colour, unsigned int alpha);
		void SetColour(const wxColour& colour);
		void SetAlpha(unsigned int alpha);
		unsigned int GetAlpha() const {return m_alpha;};
		const wxColour& GetColour() const {return m_bgColour;};
	private:
		void DrawButton();
		wxColour m_bgColour;
		unsigned int m_alpha;
	};

	class TransparencyDlg : public wxDialog {
	public:
		TransparencyDlg(wxWindow *parent, unsigned int alpha);
		unsigned int GetAlpha() const {return m_slider->GetValue();};
	private:
		wxSlider* m_slider;
	};

	class FocusTextCtrl : public wxTextCtrl {
	public:
		FocusTextCtrl(ThemeEditor& parent, wxWindowID id);
	private:
		void OnKillFocus(wxFocusEvent& event);
		DECLARE_EVENT_TABLE();
		ThemeEditor& m_parentDlg;
	};

	struct CopyColours {
		CopyColours() {
			this->row = this->col = -1;
			this->hasCopyColour = false;
			this->hasPasteColour = false;
		};

		CopyColours(int _row, int _col, wxColour _copyColour, unsigned int _copyAlpha) {
			this->row = _row; this->col = _col;
			this->hasCopyColour = true;
			this->copyColour = _copyColour;
			this->copyAlpha = _copyAlpha;
			this->hasPasteColour = false;
		};

		CopyColours(int _row, int _col, wxColour _copyColour, unsigned int _copyAlpha, wxColour _pasteColour, unsigned int _pasteAlpha) {
			this->row = _row; this->col = _col;
			this->hasCopyColour = true;
			this->copyColour = _copyColour;
			this->copyAlpha = _copyAlpha;
			this->hasPasteColour = true;
			this->pasteColour = _pasteColour;
			this->pasteAlpha = _pasteAlpha;
		};

		int row, col;

		bool hasCopyColour;
		wxColour copyColour;
		unsigned int copyAlpha;
		bool hasPasteColour;
		wxColour pasteColour;
		unsigned int pasteAlpha;
	};

	// Member variables
	ITmThemeHandler& m_syntaxHandler;
	PListHandler& m_plistHandler;
	PListDict m_themeDict;
	std::vector<PListHandler::cxItemRef> m_themes;
	int m_themeNdx;
	int m_currentRow;
	wxArrayInt m_selection;
	CopyColours copyColours;

	// Member Ctrls
	wxTextCtrl* m_fontDesc;
	wxListBox* m_themeList;
	wxGrid* m_grid;
	FocusTextCtrl* m_selectorCtrl;
	ColourButton* m_fgButton;
	ColourButton* m_bgButton;
	ColourButton* m_selButton;
	ColourButton* m_invButton;
	ColourButton* m_lineButton;
	//ColourButton* m_caretButton;
	ColourButton* m_gutterButton;
	ColourButton* m_searchButton;
	ColourButton* m_multiButton;
	ColourButton* m_bracketButton;
	wxButton* m_gridPlus;
	wxButton* m_gridMinus;
	wxButton* m_themePlus;
	wxButton* m_themeMinus;
	wxComboBox* m_qualityCombo;
};

#endif // __THEMEEDITOR_H__
