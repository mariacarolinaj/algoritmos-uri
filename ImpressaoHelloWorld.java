import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

public class ImpressaoHelloWorld {
    public static void main(String args[]) {        
        FabImpressaoAbstrata fabricaImpressao = new FabImpressaoConcreta();        
        Impressora impressora = new Impressora(fabricaImpressao);        
        impressora.imprimir();
    }
}

class Impressora {
    private ImpressaoTela impressaoTela;
    private ImpressaoArquivo impressaoArquivo;
    
    Impressora (FabImpressaoAbstrata fabricaImpressao) {
        impressaoTela = fabricaImpressao.createImpressaoTela();
        impressaoArquivo = fabricaImpressao.createImpressaoArquivo();
    }
    
    void imprimir() {
        // decide a forma de impressão randomicamente
        Random gerador = new Random();
        int decisao = gerador.nextInt();
        
        if(decisao % 2 == 0) {
            System.out.println("A impressão está sendo realizada em tela...");
            impressaoTela.imprimir();
            
        } else {
            System.out.println("A impressão está sendo realizada em arquivo...");
            impressaoArquivo.imprimir();
        }
    }
}

interface FabImpressaoAbstrata {
    ImpressaoTela createImpressaoTela();
    ImpressaoArquivo createImpressaoArquivo();
}

class FabImpressaoConcreta implements FabImpressaoAbstrata {

    @Override
    public ImpressaoTela createImpressaoTela() {
        return new ImpressaoTela();
    }
    @Override
    public ImpressaoArquivo createImpressaoArquivo() {
        return new ImpressaoArquivo();
    }
}

interface TipoImpressao {
    void imprimir();
}

class ImpressaoTela implements TipoImpressao {
    @Override
    public void imprimir() {
        System.out.println("Hello, World");
    }
}

class ImpressaoArquivo implements TipoImpressao {
    @Override
    public void imprimir() {
        try {
            File arquivo = new File ("Impressao.txt");

            arquivo.createNewFile();

            FileWriter fileWriter = new FileWriter(arquivo, false);
            PrintWriter printWriter = new PrintWriter(fileWriter);

            printWriter.print("Hello, World");
            
            printWriter.flush();
            printWriter.close();
        } catch (IOException exception) {
            System.out.println("Erro ao tentar realizar impressão em arquivo.");
        }
    }
}