#ifndef OFX_IMPORT_H
#define OFX_IMPORT_H

#include "defs.h"
#include <libofx/libofx.h>
#include <vector>
#include "Model_Checking.h"

class mmOFXImport
{
public:
    mmOFXImport() {};
    ~mmOFXImport() {};

    // Main import function
    bool import(const wxString& file);

private:
    // Callback functions for libofx
    static void ofx_proc_transaction_cb(struct OfxTransactionData data, void* user_data);
    static void ofx_proc_account_cb(struct OfxAccountData data, void* user_data);
    
    // Helper functions
    bool processTransaction(const OfxTransactionData& transaction);
    bool processAccount(const OfxAccountData& account);
    
    // Storage for imported data
    std::vector<Model_Checking::Data> m_transactions;
    std::map<wxString, int64_t> m_account_map; // Maps OFX account IDs to MMEX account IDs
};

#endif // OFX_IMPORT_H 