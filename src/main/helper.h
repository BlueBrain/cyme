//random generator
static boost::random::uniform_real_distribution<float>    RandomDouble = boost::random::uniform_real_distribution<float>(-5,5);
static boost::random::uniform_real_distribution<double>   Randomfloat  = boost::random::uniform_real_distribution<double>(-5,5);
static boost::random::mt19937    rng;

template<class T>
T GetRandom();

template<>
float GetRandom<float>(){
    return Randomfloat(rng);
}

template<>
double GetRandom<double>(){
    return RandomDouble(rng);
}

template<class T, memory::order O>
struct helper_pointer{};

template<class T>
struct helper_pointer<T, memory::AoS>{
      static inline T get(T& a){return a;}
};

template<class T>
struct helper_pointer<T, memory::AoSoA>{
      static inline T* get(T& a){return &a;}
};


template<class T, memory::order O>
struct Solver_add;

template<class T>
struct Solver_add<T, memory::AoS>{ 
   typedef T value_type;
   static const memory::order O = memory::AoS;
   static inline void op(value_type a,value_type b){
       numeric::add(a,b);
   };   
   static const std::string name(){ return "add AoS"; };
};          

template<class T>
struct Solver_add<T, memory::AoSoA>{ 
   typedef T value_type;
   static const memory::order O = memory::AoSoA;
   static inline void op(value_type* a, const value_type* b){
       numeric::add(a,b);
   };   
   static const std::string name(){ return "add AoSoA"; };
};          
     
template<class T, memory::order O>
struct Solver_exp_tim;
        
template<class T>
struct Solver_exp_tim<T, memory::AoS>{
   typedef T value_type;
   static const memory::order O = memory::AoS;
   static inline void op(value_type a,value_type b){
       numeric::exp<T,14>(a,b);
   };   
   static const std::string name(){ return "exp AoS"; };
};      
        
template<class T>
struct Solver_exp_tim<T, memory::AoSoA>{
   typedef T value_type;
   static const memory::order O = memory::AoSoA;
   static inline void op(value_type* a, const value_type* b){
       numeric::exp<T,14>(a,b);
   };   
   static const std::string name(){ return "exp AoSoA"; };
};      

template<class T, memory::order O> 
struct Solver_exp_ibm;
        
template<class T>
struct Solver_exp_ibm<T, memory::AoS>{
   typedef T value_type;
   static const memory::order O = memory::AoS;
   static inline void op(value_type a,value_type b){
       a = exp(b);
   };   
   static const std::string name(){ return "system exp AoS"; };
};     
   
typedef Solver_add<float,memory::AoS>    fadd_s;
typedef Solver_add<float,memory::AoSoA>  fadd_v;
typedef Solver_exp_tim<float,memory::AoS>  fexp_s_tim;
typedef Solver_exp_tim<float,memory::AoSoA>  fexp_v_tim;
typedef Solver_exp_ibm<float,memory::AoS>  fexp_s_ibm;

typedef Solver_add<double,memory::AoS>  dadd_s;
typedef Solver_add<double,memory::AoSoA>  dadd_v;
typedef Solver_exp_tim<double,memory::AoS>  dexp_s_tim;
typedef Solver_exp_tim<double,memory::AoSoA>  dexp_v_tim;
typedef Solver_exp_ibm<double,memory::AoS>  dexp_s_ibm;
   
typedef boost::mpl::vector<
                           fadd_s,
                           fadd_v,
                           fexp_s_tim,
                           fexp_v_tim,
                           fexp_s_ibm,
                           dadd_s,
                           dadd_v,
                           dexp_s_tim,
                           dexp_v_tim,
                           dexp_s_ibm
                           > Solver_op_list;

typedef boost::mpl::vector<
                           fadd_s,
                           fadd_v
                           > Solver_op_list_2;

