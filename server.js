const express = require('express')
const app = express()

express.static.mime.define({ 'application/wasm': ['wasm'] })
app.use(express.static('public'))

app.listen(8888, () => console.log('Server running on port 8888'))
