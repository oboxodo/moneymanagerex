#include "ofx_import.h"
#include "Model_Account.h"
#include "Model_Checking.h"

bool mmOFXImport::import(const wxString& file)
{
    LibofxContextPtr ctx = libofx_get_new_context();
    ofx_set_transaction_cb(ctx, ofx_proc_transaction_cb, this);
    ofx_set_account_cb(ctx, ofx_proc_account_cb, this);
    
    // Process the file
    libofx_proc_file(ctx, file.ToStdString().c_str(), AUTODETECT);
    
    libofx_free_context(ctx);
    
    // Save imported transactions
    if (!m_transactions.empty())
    {
        // Check for duplicates
        for (auto& trx : m_transactions)
        {
            wxDate dt;
            dt.ParseISODate(trx.TRANSDATE);
            const auto existing = Model_Checking::instance().find(
                Model_Checking::TRANSDATE(dt),
                Model_Checking::ACCOUNTID(trx.ACCOUNTID),
                Model_Checking::TRANSAMOUNT(trx.TRANSAMOUNT)
            );
            
            if (!existing.empty())
            {
                trx.STATUS = Model_Checking::STATUS_KEY_DUPLICATE;
            }
        }
        
        // Save transactions
        Model_Checking::instance().save(m_transactions);
    }
    
    return true;
}

void mmOFXImport::ofx_proc_transaction_cb(struct OfxTransactionData data, void* user_data)
{
    mmOFXImport* ofx_import = static_cast<mmOFXImport*>(user_data);
    ofx_import->processTransaction(data);
}

bool mmOFXImport::processTransaction(const OfxTransactionData& ofx_tx)
{
    Model_Checking::Data trx;
    
    // Convert OFX transaction data to MMEX transaction
    trx.TRANSDATE = wxString::FromUTF8(ofx_tx.date);
    trx.TRANSAMOUNT = ofx_tx.amount;
    trx.NOTES = wxString::FromUTF8(ofx_tx.memo);
    trx.TRANSACTIONNUMBER = wxString::FromUTF8(ofx_tx.check_number);
    
    // Find or create payee
    wxString payee_name = wxString::FromUTF8(ofx_tx.name);
    int payee_id = Model_Payee::instance().lookup(payee_name);
    trx.PAYEEID = payee_id;
    
    // Map OFX account to MMEX account
    wxString account_id = wxString::FromUTF8(ofx_tx.account_id);
    if (m_account_map.find(account_id) != m_account_map.end())
    {
        trx.ACCOUNTID = m_account_map[account_id];
    }
    
    m_transactions.push_back(trx);
    return true;
} 