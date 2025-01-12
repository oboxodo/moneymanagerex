#include "ofx_import_gui.h"

bool mmOFXImportDialog::Create(wxWindow* parent)
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    
    if (!wxDialog::Create(parent, wxID_ANY, _("OFX Import")))
        return false;
    
    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    
    SetIcon(mmex::getProgramIcon());
    Centre();
    
    return true;
}

void mmOFXImportDialog::OnOk(wxCommandEvent& WXUNUSED(event))
{
    if (m_file_path.empty())
    {
        wxMessageBox(_("Please choose OFX file to import"), _("OFX Import"), wxOK | wxICON_ERROR);
        return;
    }
    
    if (ImportOFX())
    {
        EndModal(wxID_OK);
    }
}

bool mmOFXImportDialog::ImportOFX()
{
    wxBusyCursor wait;
    wxString msg;
    
    if (!m_ofx_import.import(m_file_path))
    {
        msg = _("Error importing OFX file");
        wxMessageBox(msg, _("OFX Import"), wxOK | wxICON_ERROR);
        return false;
    }
    
    msg = _("Import successful");
    wxMessageBox(msg, _("OFX Import"), wxOK | wxICON_INFORMATION);
    return true;
} 