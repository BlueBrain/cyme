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
struct Solver_add;

template<class T>
struct Solver_add<T, memory::AoS>{ 
   typedef T value_type;
   static const memory::order O = memory::AoS;
   static inline void op(value_type& a, const value_type& b){
       numeric::add(a,b);
   };

    static inline void ops(value_type& a, const value_type& b){
        op(a,b);
    };

   static const std::string name(){ return "+ AoS"; };
};          

template<class T>
struct Solver_add<T, memory::AoSoA>{ 
   typedef T value_type;
   static const memory::order O = memory::AoSoA;
   static inline void op(value_type& a, const value_type& b){
       numeric::add(&a,&b);
   };

   static inline void ops(value_type* a, const value_type* b){
       numeric::add(a,b);
   };

   static const std::string name(){ return "+ AoSoA"; };
};          
     
template<class T, memory::order O>
struct Solver_exp_tim;
        
template<class T>
struct Solver_exp_tim<T, memory::AoS>{
   typedef T value_type;
   static const memory::order O = memory::AoS;
   static inline void op(value_type& a, const value_type& b){
       numeric::exp<T,14>(a,b);
   };

   static inline void ops(value_type& a, const value_type& b){
        op(a,b);
   };

    
   static const std::string name(){ return "e AoS"; };
};      
        
template<class T>
struct Solver_exp_tim<T, memory::AoSoA>{
   typedef T value_type;
   static const memory::order O = memory::AoSoA;
   static inline void op(value_type* a, const value_type* b){
       numeric::exp<T,14>(a,b);
   };

   static inline void ops(value_type* a, const value_type* b){
       numeric::exp<T,14>(a,b);
   };

   static const std::string name(){ return "e AoSoA"; };
};      

template<class T, memory::order O> 
struct Solver_exp_system;
        
template<class T>
struct Solver_exp_system<T, memory::AoS>{
   typedef T value_type;
   static const memory::order O = memory::AoS;
   static inline void op(value_type& a, const value_type& b){
       a = exp(b);
   };

   static inline void ops(value_type& a, const value_type& b){
       op(a,b);
    };


   static const std::string name(){ return "system e AoS"; };
};     
   
typedef Solver_add<float,memory::AoS>    fadd_s;
typedef Solver_add<float,memory::AoSoA>  fadd_v;
typedef Solver_exp_tim<float,memory::AoS>  fexp_s_tim;
typedef Solver_exp_tim<float,memory::AoSoA>  fexp_v_tim;
typedef Solver_exp_system<float,memory::AoS>  fexp_s_system;

typedef Solver_add<double,memory::AoS>  dadd_s;
typedef Solver_add<double,memory::AoSoA>  dadd_v;
typedef Solver_exp_tim<double,memory::AoS>  dexp_s_tim;
typedef Solver_exp_tim<double,memory::AoSoA>  dexp_v_tim;
typedef Solver_exp_system<double,memory::AoS>  dexp_s_system;
   
typedef boost::mpl::vector<
                           fadd_s,
                           fadd_v,
                           fexp_s_tim,
                           fexp_s_system,
                           fexp_v_tim,
                           dadd_s,
                           dadd_v,
                           dexp_s_tim,
                           dexp_v_tim,
                           dexp_s_system
                           > Solver_op_list;

typedef boost::mpl::vector<
                           fadd_s,
                           fadd_v
                           > Solver_op_list_2;

