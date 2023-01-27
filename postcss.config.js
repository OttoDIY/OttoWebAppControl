// PostCSS configuration
module.exports = cfg => {

    // import tokens as Sass variables
    const variables = require('./tokens.json');

    const
      dev = cfg.env === 'development',
      scss = cfg.file.extname === '.scss';

    return {

      map: dev ? { inline: false } : false,
      parser:  scss ? 'postcss-scss' : false,
      plugins: [
        require('postcss-advanced-variables')({ variables }),
        require('postcss-map-get')(),
        require('postcss-nested')(),
        require('postcss-sort-media-queries')(),
        require('postcss-assets')({
          loadPaths: ['src/images/']
        }),
        require('autoprefixer')(),
        dev ? null : require('cssnano')()
      ]

    };

  };