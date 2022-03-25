/* CFile
 * 
 * FileName     [testfirst.c]
 * 
 * SystemName   [ABC: Logic synthesis and verification system]
 * 
 * PackageName  [Getting Started with ABC]
 * 
 * Synopsis     [Main functions for our new commands]
 * 
 * Author       [Ana Petkovska]
 * 
 * Affiliation  [EPFL IC LAP]
 * 
 * Date         [Ver. 1.0 Started - March 24, 2022]
 * 
 * Revision     []
 * 
*/

#include "base/main/main.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////
///              FUNCTION DEFINITIONS                ///
////////////////////////////////////////////////////////

int TestFirst_FirstFunction(Abc_Ntk_t* pNtk);

/* Function
 *
 * Synopsis     [The function for our first command.]
 * 
 * Description  [Extracts the ABC network and executes the main function for the command]
 * 
 * SideEffects  []
 * 
 * SeeAlso      []
 */

int TestFirst_FirstFunctionAbc(Abc_Frame_t* pAbc) {
    Abc_Ntk_t* pNtk;
    int result;

    // Get the network that is read into ABC
    pNtk = Abc_FrameReadNtk(pAbc);

    if (pNtk == NULL) {
        Abc_Print(-1, "TestFirst_FirstFunctionAbc: Getting the target network has failed.\n");
        return 0;
    };

    // Call the main function
    result = TestFirst_FirstFunction(pNtk);
    return result;
}

int TestFirst_FirstFunction(Abc_Ntk_t* pNtk) {
    // check if the network is strashed
    if (!Abc_NtkIsStrash(pNtk)) {
        Abc_Print(-1, "TestFirst_FirstFunction: This command is only applicable to strashed networks.\n");
        return 0;
    };

    // print information about the network
    Abc_Print(1, "The network with name %s has:\n", Abc_NtkName(pNtk));
    Abc_Print(1, "\t- %d primary inputs;\n", Abc_NtkPiNum(pNtk));
    Abc_Print(1, "\t- %d, primary outputs;\n", Abc_NtkPoNum(pNtk));
    Abc_Print(1, "\t- %d AND gates.\n", Abc_NtkNodeNum(pNtk));

    return 1;
};

////////////////////////////////////////////////////////
///                  END OF FILE                     ///
////////////////////////////////////////////////////////

ABC_NAMESPACE_IMPL_END