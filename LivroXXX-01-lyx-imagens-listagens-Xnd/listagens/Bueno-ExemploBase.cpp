import std;

// =========================================================================> TIPOS
 [1] bool	booleano = 0 ->	1
 [1] char c = -128 -> 127;                   unsigned char c = 0 -> 255;
 [2] wchar_t	wc = 0	-> 65535
 [2] short s =-32768 -> 32767;               unsigned short s = 0 -> 65535;
 [4] int i =-2.147.483.648 -> 2.147.483.647; unsigned int i = 0 -> 4.294.967.295;
 [8] long long l = -9.223.372.036.854.775.808 -> 9.223.372.036.854.775.807; ul= 18.446.744.073.709.551.615
 [4] float	precisão simples 7 dígitos	1.17e-38 ->	3.40e+38
 [8] double	precisão dupla 15 dígitos	1.7e-308 ->	1.7e+308
 [16] long double	precisão dupla 19 dígitos	3.4e-4932 ->	1.1e+4932
 [4] enum	enumerados	-2.147.483.648 ->	+2.147.483.648
// [ ] ---------------------------------------------------------------------> auto
 auto x { 1 };                 // int
 auto Pi() { return 3.1415 };  // retorna double
 double x = 123'456'789;       // legibilidade
// [ ] ---------------------------------------------------------------------> referencia e ponteiro
 auto& rx = x;                 // int& refx = x;
 auto* px = &x;                // int * px  = &x;
 int && rvalue_refecence = x;  // rvalue reference
 int&& var1 = 10;
// [ ] ---------------------------------------------------------------------> STRING
 using namespace std::string_literals;
 std::string s = "Uma string C++ "s;
 std::string_view sv = "Texto"; // string leve, somente leitura
// [ ] ---------------------------------------------------------------------> format
 cout << std::format("{} {}!", "Hello", "world", "algo mais");
// [ ] ---------------------------------------------------------------------> variadic template
 template<typename... Args>
 auto Soma(Args... args) { return args + ...; }
// [ ] ---------------------------------------------------------------------> enum class: tipo
 enum class EMesesAnoCpp11: unsigned int { janeiro = 1, fevereiro, marco, abril,..};
// =========================================================================> INICIALIZAÇÃO
// [ ] ----------------------------------------------------------------> Inicialização uniforme
 std::vector vx { 0, 1, 2, 4, 5 };
// [ ] ---------------------------------------------------------------------> constexpr/constinit/consteval
 constexpr int FuncaoConstante() { return 5; }    // Tempo compilação
 const char* FS() { return "retorna cstring 1"; }
 constexpr const char *F(bool b) { return b ? "retorna cstring 2" : FS(); }
 constinit const char *c = F(true);
 consteval int sqr(int n) { return n*n; }
// [ ] ---------------------------------------------------------------------> unique_ptr
 std::unique_ptr<int> ptr_int3( new int(3) );     // Cria ponteiro e objeto
 unique_ptr<int> ptr_int5  = std::move(ptr_int3); // Transfere propriedade
 ptr_int5.reset();                                // Destrõe
 ptr_int3.reset();                                // Não faz nada.
 std::unique_ptr<ClasseX> v = std::make_unique<ClasseX>();
 std::unique_ptr<ClasseX> v = std::make_unique<ClasseX>(p1,p2,p3);
// [ ] ---------------------------------------------------------------------> shared_ptr
 shared_ptr<int> ptr_int6(new int(6));            // Cria ponteiro e objeto
 ptr_int6.reset();                                // Só destroi se for ultimo
// [ ] -----------------------------------------------------------------> Lista inicialização
 class CLista { private:  vector< float > v;
               public:   CLista( std::initializer_list<float> lista ): v(lista){};
                         vector< float > V()	{ return v; }; };
// =========================================================================> CONTROLE
// [ ] ---------------------------------------------------------------------> static_assert
 static_assert(constant-expression, error-message);// Mensagem de erro em tempo de compilação
 static_assert(constant-expression);// --> static_assert sem mensagem;
 static_assert(std::is_integral<T>::value, "O parâmetro de f deve ser do tipo integral.");
// [ ] ---------------------------------------------------------------------> range based for
 int vetor_estilo_c[5] = { 1, 2, 3, 4, 5 };
 for( auto& elemento_vetor : v )             cout << elemento_vetor << endl;
// [ ] ---------------------------------------------------------------------> if e switch.
 if(inicialização, condição) {...}
 if(int x=4; x+j<4) {...j--...}
// funciona como static-if para o C++. Reduz uso de SFINAE.
 if constexpr (is_floating_point_v<T>) {}
// =========================================================================> FUNÇÕES
// --> expecificação de exceções passam a ser parte do tipo da função;
// [ ] ---------------------------------------------------------------> Novo formato funções
 auto X() -> int	{ return x; } // retorna int
 auto X(int _x) 	{ x = _x; }   // retorno deduzido como int
// [ ] ---------------------------------------------------------------------> rvalue reference
 template<typename T> void f(T&& param);                 // parâmetro do tipo rvalue reference
 template<typename T> void f(std::vector<T>&& param);
// [ ] ---------------------------------------------------------------------> Funções lambda
 int soma = 0; // captura por referencia &
 auto Soma = [&soma]( int x ) { soma += x; cout << "Soma = " << soma << endl; };
 --> uso de [=, this] para capturar this.
 --> funções lambda declaradas dentro de métodos membro capturam automaticamente this;
  a captura de *this cria uma cópia do objeto.
 --> agora constexpr pode ser usada com lambda
 constexpr auto N = [] (int n) { return n;}
 static_assert ( N(5) == 5 );
// [ ] ---------------------------------------------------------------------> function
 #include <functional>
 function<double(double)> fx2 = [](double x) { return x*x;};  // funcao f
// [ ] ---------------------------------------------------------------------> bind
 void fis( int x, string s) { cout << "int x = " << x << " string s = " << s << endl; }
 fis( 2, " oi tudo bem ");
 // Cria ponteiro para função fis que recebe apenas a string
 std::function<void( string )> fs = std::bind(&fis, 3 , std::placeholders::_1);
 fs("Usando fs, passando apenas a string");
// [ ] ---------------------------------------------------------------------> Ponteiro Função
 using PonteiroFuncao = void (*)(double); PonteiroFuncao = f;
 std::function<void(int)> pF11 = &F11;
 auto autopF11 = &F11;
 class C {    void F11(int x)   { cout << "F11 x=" << x << endl; } };
 std::function<void (C&, int)> pF11_ref = &C::F11; // funciona como referencia
 std::function<void (C*, int)> pF11_ptr = &C::F11; // funciona como ponteiro
// =========================================================================> CLASSES
// [ ] ----------------------------------------------------------------> delegação construtor
 explicit CPonto (int _x, int _y):x(_x),y(_y) 	{}
 CPonto(int xy) : CPonto(xy,xy) 	{}  // um construtor chama o outro
// [ ] ---------------------------------------------------------------------> default e delete
 class NonCopyable { public:  // desabilitar operator= (não criar)
  NonCopyable& operator=(const NonCopyable&) = delete;
  NonCopyable(const NonCopyable&) = delete; // desabilita cópia
  NonCopyable() = default;                  // Pede para criar construtor default
// [ ] ---------------------------------------------------------------------> override e final
 class CPonto { virtual auto Entrada() -> void; virtual auto Saida() -> void; };
 class CCirculo: public CPonto {
    virtual void Entrada() override ; // sobrescreve método virtual da classe base
    virtual void Saida() final; };    // última atualização de Saida
// [ ] ---------------------------------------------------------------------> sizeof mebro
 class CPonto { public: double x; double y;};
 cout << "sizeof(CPonto::x) = " << sizeof(CPonto::x) << endl;
// [ ] ---------------------------------------------------------------------> atributos inline
 class X { static inline const double pi = 3.1415; };

// =========================================================================> ATRIBUTOS
 [[nodiscard]]     // Informa se o retorno da função foi desconsiderado!
 [[maybe_unused]]  // Compilador desconsidera se não for usado
 [[likely]]
 [[unlikely]]
 [[no_unique_address]]
// =========================================================================> CONCEPTS
 --> adição de concepts ou conceitos, expandindo as possibilidades de uso dos templates.
 COMPLETAR! Exemplo
// =========================================================================> COROUTINES
 co_await para suspender a execução até retomar.
 co_yield para suspender a execução retornando um valor.
 co_return para completar a execução retornando um valor.
 COMPLETAR! Exemplo
// =========================================================================> BIBLIOTECA
// [ ] ---------------------------------------------------------------------> std::array
 std::array<int, 4> array_4_int { {1,2,3,4} };    	// Precisa de duplo {}
 array<int, 3> array_3_int = {1, 2, 3};   		    // Apos = precisa {} simples
// [ ] ---------------------------------------------------------------------> std::pair
 std::pair<double,bool> pdb(5.0, false);
 auto pdd = make_pair(1.1,2.2);
 cout << "get<0>(p) = " << get<0>(pdb) 	<< " , get<1>(p) = " << get<1>(pdb);
 cout << "p.first   = " << p.first 	<< " , p.second  = " 	<< p.second ;
// [ ] ---------------------------------------------------------------------> std::tuple
 tuple<double, double, double> notasJoao(8.7,4.2,5.7);
 cout<< "\nJoao\n" << "P2: " << get<1>(notasJoao); // 4.2
 std::get<2>(notasJoao) = 6.3; // Nota p3 corrigida, usa referencia.
// Mostra uso da funcao tie() para obter, separadamente, os valores da tuple
 auto [n1, n2, n3] = notasJoao;
 cout<< "\nJoao\n" << "n1: " << n1 << ", " << "n2: " << n2 << ", " << "n3: " << n3 << '\n';
// [ ] ---------------------------------------------------------------------> matemática
--> uso de funções matemática especiais - Mathematical Special Functions.
 bessel, laguerre, hermite, neumann, beta
// [ ] ---------------------------------------------------------------------> std::optional
std::optional<int> opt = {};
std::cout << opt.value_or(2); // mostra 2
opt = 1;
std::cout << opt.value_or(2); // mostra 1
std::cout << *opt << '\n';
try { [[maybe_unused]] int n = opt.value(); }
catch(const std::bad_optional_access& e) { std::cout << e.what() ; }
std::optional<double> d = opt.transform(to_double);// [ ] ---------------------------------------------------------------------> std::any
std::any a = 1;
a.emplace<float>(2.0);
float valor = std::any_cast<float>(&a);
a.reset();
std::cout << "a.has_value(): " << a.has_value() << "\n";
std::cout << "a is int: " << std::any_cast<int>(a) << '\n';
auto as = std::make_any<std::string>("Hello std::any!\n");
// [ ] ---------------------------------------------------------------------> std::variant
std::variant<int, std::string> vs = "msg";
std::cout << "vs.index = " << vs.index() << '\n';// [ ]
vs.emplace<1>("msg");
std::cout << "get<int>(cp) = " << std::get<int>(cp); << "get<0>(cp) = " << std::get<0>(cp);
std::variant<int, std::string> v1{1}, v2{"msg"};
std::visit([] (auto&& x) { std::cout << x << ' '; }, v1);
// [ ] ---------------------------------------------------------------------> std::expected
std::expected<double, int> ex = std::unexpected(3);
 if (!ex) std::cout << "ex contains an error value\n";
 if (ex == std::unexpected(3)) std::cout << "The error value is equal to 3\n";
---------------------------------------------------------------------> std::except
 COMPLETAR! Exemplo
// [ ] ---------------------------------------------------------------------> std::filesystem
 namespace fs = std::filesystem;
 int main() {
 auto p = fs::current_path();
 std::cout   << "\n================Informações da path======================"
            << "\nPath completa: " << p
            << "\nNote que o Caminho corrente pode ser decomposto nas seguintes partes:"
            << "\nroot_name()="       << p.root_name()
            << "\nroot_directory()="  << p.root_directory()
            << "\nroot_path()="       << p.root_path()
            << "\nroot_path().string() =" << p.root_path().string()
            << "\nparent_path()="     << p.parent_path()
            << "\nfileName()="        << p.fileName()
            << "\nextension()="       << p.extension();
            << "\nis_block_file (device)     = " << is_block_file(p)
            << "\nis_character_file (device) = " << is_character_file(p)
            << "\nis_directory               = " << is_directory(p)
            << "\nis_fifo                    = " << is_fifo(p)
            << "\nis_other                   = " << is_other(p)
            << "\nis_regular_file            = " << is_regular_file(p)
            << "\nis_socket                  = " << is_socket(p)
            << "\nis_symlink                 = " << is_symlink    (p)
            << "\nis_empty                   = "  << fs::is_empty(p)
            << "\nexists                     = "  << fs::exists(p);
    // Também posso criar uma path, um caminho para um arquivo
    fs::path p1 = "/tmp/teste/imagens/img1.pgm";
    ofstream img1(p1);                          // Cria arquivo
    string spgm = "p4 \n2 2 4\n1 2\n3 4\n" ;    // Cria string com conteúdo arquivo processado
    img1 << spgm;                               // Substitui conteúdo do arquivo
    img1.close();                               // Fecha o arquivo antes de mudar seu nome
    // Arquivo com . no nome
    fs::path p2 = "/tmp/teste/imagens/img1.processada.pbm";
    // Caso em que o arquivo tem . só tem extensão (arquivo oculto no GNU/Linux)
    fs::path p3 = "/tmp/teste/imagens/.arquivoOcultoNoLinux";
 std::cout   << "\n================DISCO======================";
    // Informações de espaço em disco
    fs::space_info home = fs::space("/home");
    cout  <<"\nDiretório" << "Capacidade"     << "Livre"     <<  "Disponível\n"
         << setw(20) << "/home: " << setw(20) << home.capacity << setw(20)
         << home.free << setw(20) << " " << home.available  << '\n';
 std::cout   << "\n================DIRETÓRIOS======================";
    // Criando um diretório e tentando copiar
    fs::path dir1 = "/tmp/teste/imagens";
    fs::path dir2 = "/tmp/teste/imagens.backup";
    fs::create_directory("/tmp/teste/");
    fs::create_directory("/tmp/teste/imagens");
    try {
        fs::copy_file(p1, "/tmp/teste/imagens/img1.pbm");
    } catch(fs::filesystem_error& e) {
        cout << "\nNão deu para copiar o arquivo /tmp/teste/imagens/img1.pgm: " << e.what() << '\n';
    }
    try { fs::copy(dir1, dir2);                       // Cópia sem recursão e com recursão
          fs::copy("/tmp/teste/imagens",
                 "/tmp/teste/imagens.backup2", fs::copy_options::recursive);
    } catch(fs::filesystem_error& e) {
        std::cout << "Não deu para copiar o diretório: " << e.what() << '\n';    }
    //fs::remove_all("/tmp/teste"); // Removendo diretório
    // Iterando pelo diretório
    cout << "\nVai iterar não recursivamente pelo diretório e mostrar as paths :";
    for(auto& arq: fs::directory_iterator("/tmp/teste"))  // Itera pelo diretório
        cout << arq << '\n';                         // e mostra path dos arquivos
    // Iterando recursivamente pelo diretório
    cout << "\nVai iterar recursivamente pelo diretório e mostrar as paths :";
    for(auto& arq: fs::recursive_directory_iterator("/tmp/teste")) // Itera recursivamente
        cout << arq << '\n';                        // e mostra arquivos
 std::cout   << "\n================ARQUIVOS======================";
    // Criação e manipulação de arquivos
    cout << "\nConteúdo do arquivo: \n" << ifstream(p1).rdbuf() << '\n';
    auto p4 = p1;
    p4.replace_fileName("img1_processada");      // Substitui nome da path
    p4.replace_extension(".pbm");                // Substitui extensão da path
    p4 +=".backup";
    fs::copy(p1,p4);                             // Cópia de arquivos
 std::cout   << "\n================LINKS======================";
    cout << "\n\nVai criar links:";              // Criando links
    fs::create_hard_link("/tmp/teste/imagens/img1.pbm", "/tmp/teste/imagens/hard_link_img1.pbm");
    fs::path p5 = "/tmp/teste/imagens/hard_link_img1.pbm";// hard link simbólico
    fs::create_symlink("/tmp/teste/imagens/img1.pbm", "teste/imagens/symlink_img1.pbm");
    fs::path p6 = "/tmp/teste/imagens/symlink_img1.pbm"; // link simbólico
    fs::create_directory_symlink("/tmp/teste/imagens/","symlink_imagens");
    fs::path p7 = "symlink_imagens";             // link simbólico diretório
    system("tree /tmp/teste");
  std::cout << "Os caminhos para p1 e p2 são equivalentes? "
            << equivalent(p1,p2) << endl;
  std::cout << "O tamanho do p1 é de " <<  file_size(p1) << "bytes" << endl;
  auto ftime = fs::last_write_time(p1);
  //std::cout << "A ultima escrita no p1 ocorreu às =" << ftime  << endl; //C++20 verificar
  rename( p1,  "/tmp//teste/arquivoRenomeado.pbm" );
  std::cout << "O arquivo p1 foi renomeado para arquivoRenomeado.pbm." << endl;
  remove( p1 );   std::cout << "O arquivo p1 foi removido." << endl;
  fs::remove_all("/tmp/teste"); // Removendo diretório
 return 0;}
// [ ] ---------------------------------------------------------------------> std::random
// O gerador números randomicos tem duas partes; um motor que gera números randomicos 
// e uma distribuição matemática. 
// Motores: linear_congruential_engine,subtract_with_carry_engine e mersenne_twister_enginee.
// Distribuições: uniform_int_distribution, uniform_real_distribution, 
// bernoulli_distribution, binomial_distribution, geometric_distribution, poisson_distribution,
// normal_distribution, student_t_distribution, chi_squared_distribution, 
// exponential_distribution, gamma_distribution, lognormal_distribution, 
// cauchy_distribution, lognormal_distribution, weibull_distribution, 
// extreme_value_distribution, fisher_f_distribution, negative_binomial_distribution,  
// discrete_distribution, piecewise_constant_distribution, piecewise_linear_distribution.
#include <random>
int main()
{ uniform_int_distribution<int> distribuicao(-20, 20); // Cria distribuição uniforme
  mt19937 motor;                                       // Cria motor "Mersenne twister MT19937"
  int numeroRandomico = distribuicao(motor);           // Gera número aleatório
  std::normal_distribution<double>  normal(0.0,1.0);   // Normal, media 0 e desvio padrao 1
  cout << " media = " << normal.mean() << " desvio padrao = " << normal.stddev() 
       << " max = " << normal.max() << " min = " << normal.min() << endl;
  normal = normal_distribution<double>(12,3);          // Seta media = 12 e desvio padrao = 3

  std::default_random_engine motor2;           // Cria motor, usa default
  auto Normal = std::bind(normal, motor2);     // Cria gerador de número aleatorio
  vector<double> vna(500);                     // Cria vetor de numeros aleatorios
  for( double &ev : vna )	ev = Normal();       // Gera números aleatóros
}
// [ ] ---------------------------------------------------------------------> std::chrono
#include <chrono>  <ctime>
using namespace std::literals::chrono_literals;
auto duration = 1h + 2min + 3s + 4ms + 5us + 6ns;
  chrono::time_point<chrono::system_clock> start;
  start = chrono::system_clock::now();
  ...processamento...
  auto end = chrono::system_clock::now();
  int elapsed_seconds = chrono::duration_cast<chrono::seconds>(end-start).count();
  time_t end_time = chrono::system_clock::to_time_t(end);
  cout << "Computação terminada em  " << ctime(&end_time)
       << "tempo(s) decorrido : " << elapsed_seconds << "s\n";
// [ ] ---------------------------------------------------------------------> std::regex (-lregex)
#include <regex>	// regex, replace, match_results
// regex - Classe que representa uma Expressão Regular - ER.
// match_results - representa as ocorrências, casos em que a ER foi encontrada.
// regex_search - função usada para localizar uma ocorrência da ER.
// regex_replace - função que substitue a ocorrência encontrada por outro texto.
#include <regex> 
int main() {
  std::string ser{"Molly"}, texto{"A Molly é danadinha."};
  std::regex er {ser};             // expressão regular
  std::smatch m;                   // std::regex_match para string
  std::cout << "\nregex_match  ? " << std::regex_match  (texto, m, er )
            << "\nregex_search ? " << std::regex_search (texto, m, er )
            << "\nregex_replace? " << std::regex_replace(texto, er, "[$&]")<< '\n'; }
// [ ] ---------------------------------------------------------------------> std::threads
// Bibliotecas processamento paralelo
#include <thread> <jthread> <mutex> <condition_variable> <future> <chrono>

void f(){  std::cout << "Olá Mundo - função f." << std::endl; }
class COlaMundo { public:
 void operator(int n = 0 )(){ Ola(n);  Mundo(); }
private:
 void Ola(int n) 	{ cout << "\nclass COlaMundo: Olá " << n ; }
 void Mundo() 	    { cout << " Mundo." ; }
 void Repeat(int n) { while (n--) {Ola();  Mundo();} }
};
void FuncaoDestacada() { cout << "\nFunção destacada, id = " << this_thread::get_id() }
int main() {
std::cout   << "\n================THREADS======================";
  std::thread t1{ f };  // Cria e dispara a thread t1 função f
  thread t2([](){ cout << "nFunção lambda."}); // thread de função lambda
  COlaMundo obj;        // Cria objeto
  thread t3{obj}; 	    // Cria a thread t3
  thread t4( &FuncaoDestacada );
  t4.detach();          // Torna a thread destacada, t4 não tem mais acesso a join(), usa sleep_for
  t1.join();t2.join();  // Aguarda retorno das threads
  if(! t4.joinable())   // Verifica se não foi destacada  
   this_thread::sleep_for ( chrono::seconds(1) );  // Aguarda 1 segundo
  thread t5{&COlaMundo::Repeat,&obj,3}; // executa 3x
  thread t6 = move(t1); // Move t1 para t6
  cout  << "\nMain thread  = " << this_thread::get_id() << "\nt1.get_id() = " << t.get_id()
        << "\nNúmero de threads = " << thread::hardware_concurrency() ;
  return 0;
}
std::cout   << "\n================THREADS com vector======================";
int main() {
  std::vector<std::thread> vthreads;		// Cria vetor de threads
  for( int i = 0; i < 4; ++i )
        vthreads.push_back( std::thread(f) );	// Adiciona funções
  for( int i = 0; i < 4; ++i ) {                // Adiciona funções lambda
    vthreads.push_back( thread(
	[](){ 	cout 	<< "Função lambda: this_thread::get_id() = "
			<< this_thread::get_id() << endl;}));
    }
  for(auto& t : vthreads)
      t.join();					            // Aguarda finalização
}
std::cout   << "\n================THREADS Parâmetros======================";
void FuncaoParametrosPorCopia(string s) {
    cout << s << endl;
    s = "string s modificada em FuncaoParametrosPorCopia.";
}
void FuncaoParametroPorPonteiro(string* s) {
    cout << *s << endl;
    *s = "string s modificada em FuncaoParametroPorPonteiro.";
}
void FuncaoParametrosPorReferencia(string& s) {
    cout << s << endl;
    s = "string s modificada em FuncaoParametrosPorReferencia.";
}
int main() {
    string s = "String passada como parâmetro";
    thread t_copy(&FuncaoParametrosPorCopia, s);
    cout << "\nmain thread após FuncaoParametrosPorCopia, s = " << s ;
    thread t_pointer(&FuncaoParametroPorPonteiro, &s);
    cout << "\nmain thread após FuncaoParametroPorPonteiro, s = " << s ;
    thread t_reference2(&FuncaoParametrosPorReferencia, ref(s));
    cout << "\nmain thread após FuncaoParametrosPorReferencia, ref(s) = " << s ;
    t_copy.join(); t_pointer.join(); t_reference2.join();
}
std::cout   << "\n================THREADS MUTEX======================";
class CContador  {
    std::mutex mutex_c;    // Cria um mutex = mutual exclusion
    int contador{0};
public:                    // bloqueia, usa, libera
    void operator++() { mutex_c.lock(); ++contador; mutex_c.unlock(); }
    int Valor() { return contador; }
};
int main() {
 CContador contador;
 vector<thread> vthreads;
 for( int i = 0; i < 40; ++i ) {
  vthreads.push_back( thread( 
    [&contador]() { for(int i = 0; i < 100000; ++i){ ++contador; } }));}
 for(auto& thread : vthreads) thread.join();
 cout << contador.Valor();
}
int main() {
	mutex mutex_cout; // Mutual Exclusion para acesso a cout
	vector<thread> vt;
	for (int i = 0; i < 5; i++) {
		auto t = thread([i,&mutex_cout]() {
			mutex_cout.lock();   	// Uso de lock
			cout << "thread function: " << i << "\n";
			mutex_cout.unlock(); 	// Uso de unlock
		});
		vt.push_back(move(t)); 		// Uso de move
	}
	for (int i = -5; i < 1; i++) {
	  mutex_cout.lock();			// Uso de lock
	  cout << "main thread i =" << i << "\n";
	  mutex_cout.unlock();			// Uso de unlock
	}
	for_each(vt.begin(), vt.end(), [](thread &t) {
		assert(t.joinable());
		t.join();
	});
}
mutex mcout;                                // mutex com std::lock_guard<std::mutex>
void f1() {   for (int k = 100; k > 0; k--) {
	// lock_guard chama lock no construtor e unlock no destrutor
	std::lock_guard<std::mutex> l(mcout);
	...código compartilhado... uso de cout
	}
}
std::cout   << "\n================THREADS VARIÁVEL CONDICIONAL======================";
std::mutex mut;				                  // Cria mutex
std::queue<CData> data_queue;
std::condition_variable data_cond;	          // Cria variavel condicional
void data_preparation_thread() {	          // Prepara dados
    while(more_data_to_prepare()) {
        CData const data = prepare_data();    // Gera dados
        std::lock_guard<std::mutex> lk(mut);  // Bloqueia mutex
        data_queue.push(data);			      // Usa base de dados
        data_cond.notify_one();			      // Notifica variavel condicional
    }	}
void data_processing_thread() {
    while(true) {
	std::unique_lock<std::mutex> lk(mut);	  // Bloqueia mutex
                                              // Aguarda variavel condicional
	data_cond.wait(lk,[]{return !data_queue.empty();}); // liberacao de dados
	CData data=data_queue.front();	          // Usa base de dados
	data_queue.pop();
	lk.unlock();				              // Desbloqueia o mutex
	process(data);				              // Processa dados
	if(is_last_chunk(data))			          // Encerra processamento
		break;
    }	}
int main() {
    std::thread t1(data_preparation_thread);  // Produz dados
    std::thread t2(data_processing_thread);	  // Consome dados    
    t1.join();    t2.join();
}
std::cout   << "\n================THREADS ASYNC FUTURE======================";
int  f1() {    return 42;}
void f2(std::string const& message)  { cout << (message + "\n"); }
int main() {        // Dispara função usando async
auto a1 = async(f2,"1 - Olá mundo disparado usando async(write_message\n");
// Dispara função write_message usando std::launch::async
auto a2 = async( launch::async,f2,"1 - Olá mundo disparado usando async(launch::async,write_message,..\n" );
f2("2 - Olá mundo disparado de main\n");
// Dispara função usando async usando std::launch::deferred
auto a3 = async( launch::deferred, f2,"1 - Olá mundo disparado usando async(launch::deferred,write_message,\n" );
a1.wait();  a2.wait(); a3.wait();  // Aguarda retorno de chamada a async.

std::future<int> resultado = std::async(processar1);
thread t (processar2);
std::cout << "The answer is "<< resultado.get() << std::endl; 
t.join();   
}
int find_the_answer() { throw std::runtime_error("Unable to find the answer");}
int main() {
 auto f =  async( find_the_answer ) ; 
 try {      cout << "the answer is "<< f.get() << "\n";     }
 catch( runtime_error const& e ) { cout << "\nCaught exception: " << e.what() << endl;}
return 0;
}
std::condition_variable cv;
bool done;
std::mutex m;
bool wait_loop(){
    auto const timeout= std::chrono::steady_clock::now()+ std::chrono::milliseconds(500);
    std::unique_lock<std::mutex> lk(m);
    while(!done)    {
        if(cv.wait_until(lk,timeout)==std::cv_status::timeout) break;
    }
    return done;
}
std::cout   << "\n================THREADS PROMISE======================";
// Usando thread com future.
// AguardandoNotificacao é chamada duas vezes; e só continua quando
// usuário pressiona enter, executando o cin.get() e a seguir set_value que libera sf.get().
#include <future> #include <thread> #include <iostream> #include <sstream>
// Recebe id da thread e shared_future
void AguardandoNotificacao ( int id , std::shared_future<int> sf ) {
 ostringstream os;
 os << "Thread " << id <<" waiting\n";
 cout << os.str(); os.str("");           // Chama shared_future.get()
 os << "Thread " << id <<" woken, val=" << sf.get() << "\n";
 cout << os.str();
}
int main()  {
  std::promise<int> p;                  // Cria um promise
  auto sf = p.get_future().share(); 
  thread t1(AguardandoNotificacao, 1 ,sf);
  thread t2(AguardandoNotificacao, 2 ,sf);  
  cout << "Waiting\n"; cin.get();
  p.set_value(42);  
  t2.join(); t1.join();
  return 0;
}

============================================================================
Dicas estilo de código (código limpo)
============================================================================
- Nome classe CNomeClasse, ex: class CFuncao; class CFDarcy: public CFuncao;
- Nome objeto CFFuncao funcao2G; CFDarcy functionDarcy;
- Nome dos métodos devem indicar ação (verbos); 
ex: funcao->Salvar(fileName); funcao->Ler(fileName);
ex: funcao->SalvarDisco(fileName); funcao->LerDadosDisco(fileName);
ex: funcao2G->Read(fileName); funcao2G->Write(fileName);
ex: functionDarcy->Read(fileName); function_darcy->Plot(grafico);
Note que a codificação fica clara, auto explicativa.
Havendo necessidade pode-se colocar alguns comentários, mas a ideia é que ao usar nomes claros quase tudo fique autoexplicativo.
- Na medida do possível o nome do objeto deve dar uma indicação do nome da classe base da hierarquia a que pertence.
