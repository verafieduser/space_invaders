// void Background::render(SDL_Renderer *renderer){
//     int Xoffset = 0;
//     int Yoffset = 0;
//     for(int y = 0; (y * 411) < 1080; y++){
//         for(int x = 0; (x * 405) < 1920; x++){
//             Xoffset = 0;
//             Yoffset = 0;
//             if(GameManager::GetInstance().getGlobalX() + (405 * x) + 405 < 0){
//                 Xoffset = 1920;
//             }
//             if(GameManager::GetInstance().getGlobalY() + (411 * y) + 411 < 0){
//                 Yoffset = 1080;
//             }
//             SDL_Rect backRect = {GameManager::GetInstance().getGlobalX() + (405 * x) + Xoffset, GameManager::GetInstance().getGlobalY() + (411 * y) + Yoffset, 405, 411};
//             SDL_RenderCopy(renderer, ResourceManager::GetInstance().getTexture("background"), 0, &backRect);
//         }
//     }
// }