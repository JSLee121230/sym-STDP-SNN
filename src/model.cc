#include "model.h"
#include "add_model.cc"
//------------------------------------------------------------------------------
// POISON model P
//------------------------------------------------------------------------------
double ini_Poi[] = {
    Poi_V,
    Poi_seed,
    Poi_trace,
};
double p_Poi[] = {
    Poi_Vspike,
    Poi_Vrest,
    Poi_Ttrace,
};
//------------------------------------------------------------------------------
// LIF model E&I
//------------------------------------------------------------------------------
double ini_Exc[] = {
    Exc_V,
    Exc_theta,
    Exc_timer,
    Exc_trace1,
    Exc_trace2,
    Exc_trace,
    Exc_testDataEvaluateMode,
};
double p_Exc[] = {
    Exc_TV,
    Exc_Vrest,
    Exc_Vreset,
    Exc_Vthresh,
    Exc_Refrac,
    Exc_test_mode,
    Exc_Ttheta,
    Exc_theta_plus,
    Exc_offset,
    Exc_Ttrace1,
    Exc_Ttrace2,
    Exc_Ttrace,
};
double p_Exc_fixed[] = {
    Exc_TV,
    Exc_Vrest,
    Exc_Vreset,
    Exc_Vthresh,
    Exc_Refrac,
    Exc_test_mode,
    1e10,
    0,
    Exc_offset,
    Exc_Ttrace1,
    Exc_Ttrace2,
    Exc_Ttrace,
};
double ini_Inh[] = {
    Inh_V,
    Inh_timer,
};
double p_Inh[] = {
    Inh_TV,
    Inh_Vrest,
    Inh_Vreset,
    Inh_Vthresh,
    Inh_Refrac,
};
double ini_Cla[] = {
    Cla_V,
    Cla_seed,
    Cla_trace1,
    Cla_trace2,
    Cla_testDataEvaluateMode,
};
double p_Cla[] = {
    Cla_TV,
    Cla_Vrest,
    Cla_Vreset,
    Cla_Vthresh,
    Cla_Vspike,
    Cla_Ttrace1,
    Cla_Ttrace2,
    Cla_test_mode,
};
//------------------------------------------------------------------------------
// postSynV
//------------------------------------------------------------------------------
double postExpP2E[2] = {
    P2E_tau_S, // decay time constant for S [ms]
    P2E_Erev,  // Reversal potential
};
double postExpC2E[2] = {
    I2E_tau_S,
    I2E_Erev,
};
double postExpE2I[2] = {
    E2I_tau_S,
    E2I_Erev,
};
double postExpI2E[2] = {
    I2E_tau_S,
    I2E_Erev,
};
double *postSynV = NULL;
//------------------------------------------------------------------------------
// DA_STDP
//------------------------------------------------------------------------------
double ini_STDP_PE[] = {
    da_stdp_PE_g,
    da_stdp_PE_testDataEvaluateMode,
};
double p_STDP_PE[] = {
    da_stdp_PE_nu_ee_pre,
    da_stdp_PE_nu_ee_post,
    -da_stdp_PE_g_max,
    da_stdp_PE_g_max,
    da_stdp_PE_a_plus,
    da_stdp_PE_a_minus,
};
double ini_STDP_EC[] = {
    da_stdp_EC_g,
    da_stdp_EC_testDataEvaluateMode,
};
//------------------------------------------------------------------------------
// noSTDP
//------------------------------------------------------------------------------
double ini_noSTDP[] = {
    no_stdp_g,
};
double *p_noSTDP_PE = NULL;
double *p_noSTDP_CE = NULL;
//------------------------------------------------------------------------------
// E——>I & I——>E
//------------------------------------------------------------------------------
double ini_NSYNAPSE_EI[] = {
    g_EI,
};
double *p_NSYNAPSE_EI = NULL;
double ini_NSYNAPSE_IE[] = {
    g_IE,
};
double *p_NSYNAPSE_IE = NULL;

double ini_NSYNAPSE_CE[] = {
    g_CE,
};
double *p_NSYNAPSE_CE = NULL;

size_t size_gP2E = NPoi * NExc;
size_t size_gC2E = NExc * NCla;

void modelDefinition(NNmodel &model)
{
    initGeNN();

#ifdef DEBUG
    GENN_PREFERENCES::debugCode = true;
#else
    GENN_PREFERENCES::optimizeCode = true;
#endif
    GENN_PREFERENCES::autoRefractory = 0;

    int Poi     = addNeuronModel_Poi(nModels);
    int LIF_Exc = addNeuronModel_LIF_Exc(nModels);
    int LIF_Inh = addNeuronModel_LIF_Inh(nModels);
    int LIF_Cla = addNeuronModel_LIF_Cla(nModels);
    int STDP    = addSynapseModel_STDP(weightUpdateModels);

    model.setGPUDevice(ID_DEVICE); 
    model.setDT(DT);
    model.setPrecision(_FTYPE);
    model.setName("model");
    
    model.addNeuronPopulation("PPoi", NPoi, Poi, p_Poi, ini_Poi);
#ifndef FIXED_HIDDEN_LAYER
    model.addNeuronPopulation("PExc", NExc, LIF_Exc, p_Exc, ini_Exc);
#else
    model.addNeuronPopulation("PExc", NExc, LIF_Exc, p_Exc_fixed, ini_Exc);
#endif
    model.addNeuronPopulation("PInh", NInh, LIF_Inh, p_Inh, ini_Inh); 
    model.addNeuronPopulation("PCla", NCla, Poi, p_Poi, ini_Poi);

#ifndef test_mode
#ifndef FIXED_HIDDEN_LAYER
    model.addSynapsePopulation("P2E", STDP, DENSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PPoi", "PExc", ini_STDP_PE, p_STDP_PE, postSynV, postExpP2E);
#else
    model.addSynapsePopulation("P2E", NSYNAPSE, DENSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PPoi", "PExc", ini_noSTDP, p_noSTDP_PE, postSynV, postExpP2E); 
#endif
    model.addSynapsePopulation("C2E", NSYNAPSE, SPARSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PCla", "PExc", ini_NSYNAPSE_IE, p_NSYNAPSE_IE, postSynV, postExpI2E);
#else
    model.addSynapsePopulation("P2E", NSYNAPSE, DENSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PPoi", "PExc", ini_noSTDP, p_noSTDP_PE, postSynV, postExpP2E); 
    model.addSynapsePopulation("C2E", NSYNAPSE, DENSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PExc", "PCla", ini_noSTDP, p_noSTDP_EC, postSynV, postExpP2E);
#endif
    model.addSynapsePopulation("E2I", NSYNAPSE, SPARSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PExc", "PInh", ini_NSYNAPSE_EI, p_NSYNAPSE_EI, postSynV, postExpE2I);
    model.addSynapsePopulation("I2E", NSYNAPSE, SPARSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PInh", "PExc", ini_NSYNAPSE_IE, p_NSYNAPSE_IE, postSynV, postExpI2E);

    model.finalize();
    fprintf(stdout, "#model created.\n"); 
}
