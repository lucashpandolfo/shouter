(source
    (type             'fifo)
    (fifo-name        "song-fifo.fifo")
    (metadata-file    "metadata.lsp"))
    
(stream
    (server
        (hostname  "87.117.201.152")
        (port      19508)
        (user      "fiubalaagita")
        (password  "fiubalaagita")
        (protocol  'icy)
        (mountpoint "/stream.mp3"))

    (format 'mp3)
    (name "Radio Fiuba")
    (genre "Ensalada")
    (description "Radio FIUBA la agita")
    (url "http://foros-fiuba.com.ar"))
