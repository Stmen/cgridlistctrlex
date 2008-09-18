#pragma once

//------------------------------------------------------------------------
// Author:  Rolf Kristensen	
// Source:  http://www.codeproject.com/KB/list/CGridListCtrlEx.aspx
// License: Free to use for all
//
//! GridListCtrlEx extends the CListCtrl with the following functionality:
//!	 - Sortable
//!  - Simple column picker
//!	 - Cell navigation
//!  - Keyboard search navigation
//!  - Cell tooltip
//!  - Cell editing and customization through use of CGridColumnTrait's
//------------------------------------------------------------------------

class CGridColumnTrait;

class CGridListCtrlEx : public CListCtrl
{
public:
	CGridListCtrlEx();
	~CGridListCtrlEx();

	// CListCtrl
	LRESULT EnableVisualStyles(bool bValue);
	inline bool UsingVisualStyle() const { return m_UsingVisualStyle; }
	virtual CFont* GetCellFont();
	virtual void SetCellMargin(double margin);

	// Row
	int GetFocusRow() const;
	bool IsRowSelected(int nRow) const;
	BOOL SelectRow(int nRow, bool bSelect);

	// Column
	const CHeaderCtrl* GetHeaderCtrl() const;
	CHeaderCtrl* GetHeaderCtrl() { return CListCtrl::GetHeaderCtrl(); }
	int GetColumnData(int col) const;
	virtual BOOL EnsureColumnVisible(int nCol, bool bPartialOK);
	virtual BOOL SetColumnWidthAuto(int nCol = -1, bool includeHeader = false);
	virtual int InsertColumnTrait(int nCol, const CString& columnHeading, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1, CGridColumnTrait* pTrait = NULL);
	virtual int InsertHiddenLabelColumn();
	virtual void SetSortArrow(int colIndex, bool ascending);
	virtual BOOL ShowColumn(int nCol, bool bShow);
	virtual bool IsColumnVisible(int nCol);
	virtual int GetFirstVisibleColumn();

	// Cell / Subitem 
	void CellHitTest(const CPoint& pt, int& nRow, int& nCol) const;
	BOOL GetCellRect(int nRow, int nCol, UINT nCode, CRect& rect);
	inline int GetFocusCell() const { return m_FocusCell; }
	virtual bool ShowToolTipText(const CPoint& pt) const;
	virtual CWnd* EditCell(int nRow, int nCol);
	bool IsCellCallback(int nRow, int nCol) const;
	int GetCellImage(int nRow, int nCol) const;
	BOOL SetCellImage(int nRow, int nCol, int nImageId);

	// DataModel callbacks
	virtual bool CallbackCellText(int nRow, int nCol, CString& text) { return false; }
	virtual bool CallbackCellImage(int nRow, int nCol, int& imageId) { return false; }
	virtual bool CallbackCellCustomColor(int nRow, int nCol, COLORREF& text, COLORREF& background) { return false; }
	virtual bool CallbackCellCustomFont(int nRow, int nCol, LOGFONT& font) { return false; }
	virtual bool CallbackCellTooltip(int nRow, int nCol, CString& text);

protected:
	// Maintaining column traits (and visible state)
	CSimpleArray<CGridColumnTrait*> m_ColumnTraits;
	virtual CGridColumnTrait* GetColumnTrait(int nCol);
	virtual int GetColumnTraitSize() const;
	virtual void InsertColumnTrait(int nCol, CGridColumnTrait* pTrait);
	virtual void DeleteColumnTrait(int nCol);

	// Maintaining cell/subitem focus
	int m_FocusCell;
	void MoveFocusCell(bool right);
	void UpdateFocusCell(int nCol);

	// Maintaining Keyboard search
	CString m_LastSearchString;
	CTime	m_LastSearchTime;
	int		m_LastSearchCell;
	int		m_LastSearchRow;

	// Maintaining row sorting
	int m_SortCol;
	bool m_Ascending;
	virtual bool SortColumn(int columnIndex, bool ascending);

	// Maintaining cell editing
	CWnd* m_pEditor;

	bool m_UsingVisualStyle;

	// Maintaining margin
	CFont* m_pGridFont;
	CFont* m_pCellFont;
	CFont* m_pOldFont;
	double m_Margin;

	// Global column trait methods
	virtual void OnTraitCustomDraw(CGridColumnTrait* pTrait, NMLVCUSTOMDRAW* pLVCD, LRESULT* pResult) {}
	virtual CWnd* OnTraitEditBegin(CGridColumnTrait* pTrait, CWnd* pEditor, int nRow, int nCol) { return pEditor; }
	virtual bool OnTraitEditComplete(CGridColumnTrait* pTrait, CWnd* pEditor, LV_DISPINFO* pLVDI) { return true; }

	// Context Menu Handlers
	virtual void OnContextMenuGrid(CWnd* pWnd, CPoint point);
	virtual void OnContextMenuHeader(CWnd* pWnd, CPoint point, int nCol);
	virtual void OnContextMenuKeyboard(CWnd* pWnd, CPoint point);
	virtual void OnContextMenuCell(CWnd* pWnd, CPoint point, int nRow, int nCol);

	//{{AFX_VIRTUAL(CGridListCtrlEx)
	virtual void PreSubclassWindow();
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGridListCtrlEx)
	virtual afx_msg LRESULT OnDeleteColumn(WPARAM wParam, LPARAM lParam);
	virtual afx_msg LRESULT OnInsertColumn(WPARAM wParam, LPARAM lParam);
	virtual afx_msg BOOL OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg LRESULT OnSetColumnWidth(WPARAM wParam, LPARAM lParam);
	virtual afx_msg BOOL OnHeaderDividerDblClick(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg BOOL OnHeaderBeginResize(UINT id, NMHDR* pNmhdr, LRESULT* pResult);
	virtual afx_msg BOOL OnHeaderBeginDrag(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg BOOL OnHeaderEndDrag(UINT id, NMHDR* pNmhdr, LRESULT* pResult);
	virtual afx_msg BOOL OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg BOOL OnToolNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg BOOL OnBeginLabelEdit(NMHDR* pNMHDR,LRESULT* pResult);
	virtual afx_msg BOOL OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual afx_msg void OnContextMenu(CWnd*, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};

//{{AFX_INSERT_LOCATION}}
