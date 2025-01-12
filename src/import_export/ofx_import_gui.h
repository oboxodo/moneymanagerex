#ifndef OFX_IMPORT_GUI_H
#define OFX_IMPORT_GUI_H

#include "defs.h"
#include "ofx_import.h"

class mmOFXImportDialog : public wxDialog
{
    wxDECLARE_DYNAMIC_CLASS(mmOFXImportDialog);
    wxDECLARE_EVENT_TABLE();

public:
    mmOFXImportDialog() {};
    mmOFXImportDialog(wxWindow* parent);

    bool Create(wxWindow* parent);
    void CreateControls();
    void fillControls();
    void OnFileSearch(wxCommandEvent& event);
    void OnOk(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

private:
    mmOFXImport m_ofx_import;
    wxString m_file_path;
    wxTextCtrl* m_text_ctrl;
    wxChoice* m_account_choice;
    wxCheckBox* m_dateFormat_checkbox;
    
    bool ImportOFX();
    void updateControls();
    void updateAccountSelection();
};

#endif // OFX_IMPORT_GUI_H 