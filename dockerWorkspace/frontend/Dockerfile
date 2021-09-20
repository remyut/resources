from node:alpine as builder

WORKDIR /app
copy package.json .
run npm install
RUN mkdir node_modules/.cache && chmod -R 777 node_modules/.cache
copy . .
run npm run build

from nginx
copy --from=builder /app/build /usr/share/nginx/html
