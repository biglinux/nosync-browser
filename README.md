# nosync-browser - Make your browser faster than ever
Original code from https://www.mcgill.org.za/stuff/software/nosync 

# English

In my tests on computers with rotational HD I realized that a large part of the browsers' slowness is related to the excessive recording on disk

I do not mean the amount of data stored, but the frequency of recordings, in my tests it was not difficult with some open tabs having situations with 2 GB of data recorded per minute, using the nosync-browser, the reduction was between 80% and 90 %, that's right, from 2 GB went to somewhere between 200 MB to 400 MB

To monitor the recordings I used the command: sudo iotop -Pak

Only Firefox and Chromium worked with eatmydata, which greatly reduces disk recording, but Brave, Chrome, Opera and Vivaldi did not work with eatmydata

Nosync-browser worked on all browsers that I tested and also reduces data writing to disk by around 80%, making the system much more responsive, especially with many tabs open

The reduction of recordings on disk occurs by reducing the number of synchronizations with the storage device, increasing the time required for each recording according to the time stipulated by the file system, which is rarely more than 30 seconds, therefore in case of lack of energy, it may be that the browser loses the last seconds of history, which from my point of view is irrelevant compared to the performance gain

# Install:

Download the file
https://github.com/biglinux/nosync-browser/releases/download/1.0/nosync-browser.tar.gz

Unzip and run the install.sh file as root

Now just use nosync-browser to open your favorite browser, for example:

nosync brave-browser

# Faster

Suggested parameters that make the browser even faster:

--enable-accelerated-2d-canvas --enable-accelerated-mjpeg-decode --enable-accelerated-video --enable-features=MarkHttpAs,StrictOriginIsolation --enable-gpu-rasterization --enable-quic --use-vulkan --ignore-gpu-blocklist --enable-parallel-downloading --font-render-hinting=none --enable-zero-copy --enable-accelerated-video-decode --disable-brave-extension --disable-brave-rewards-extension


# Português

Nos meus testes em computadores com HD rotacional percebi que grande parte da lentidão dos navegadores está relacionada ao excesso de gravação em disco

Não me refiro a quantidade de dados armazenados, mas a frequência de gravações, nos meus testes não foi difícil com algumas abas abertas ter situações com 2 GB de dados gravados por minuto, utilizando o nosync-browser, a redução ficou entre 80% e 90%, isso mesmo, de 2 GB foi para algo em torno de 200 MB a 400 MB

Para monitorar as gravações utilizei o comando: sudo iotop -Pak

Apenas o Firefox e o Chromium funcionaram com o eatmydata, que reduz bastante a gravação em disco, mas os navegadores Brave, Chrome, Opera e Vivaldi não funcionaram com o eatmydata

O nosync-browser funcionou em todos os navegadores que testei e também reduz a gravação de dados em disco em torno de 80%, tornando o sistema muito mais responsivo, principalmente com muitas abas abertas

A redução das gravações em disco ocorrem reduzindo o número de sincronizações com o dispositivo de armazenamento, aumentando o tempo necessário para cada gravação de acordo com o tempo estipulado pelo sistema de arquivos, o que raramente é maior que 30 segundos, portanto no caso de falta de energia, pode ser que o navegador perca os últimos segundos do histórico, o que do meu ponto de vista é irrelevante comparado ao ganho de desempenho

# Instalar:

Faça o download do arquivo
https://github.com/biglinux/nosync-browser/releases/download/1.0/nosync-browser.tar.gz

Descompacte e execute como root o arquivo install.sh

Agora é só utilizar o nosync-browser para abrir seu navegador favorito, por exemplo:

nosync brave-browser

# Mais rápido ainda:

Sugestão de parâmetros que deixam o navegador ainda mais rápido:

--enable-accelerated-2d-canvas --enable-accelerated-mjpeg-decode --enable-accelerated-video --enable-features=MarkHttpAs,StrictOriginIsolation --enable-gpu-rasterization --enable-quic --use-vulkan --ignore-gpu-blocklist --enable-parallel-downloading --font-render-hinting=none --enable-zero-copy --enable-accelerated-video-decode --disable-brave-extension --disable-brave-rewards-extension
