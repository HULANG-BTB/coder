<?php
/**
 * FileName: Base.php
 * Product: Lazy OJ
 * Author: Hu Lang
 * DateTime: 2019/9/27 9:38
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * Description:
 *
 */

namespace app\common\controller;

use think\App;
use think\Controller;

class Base extends Controller
{
    protected $Model = null;

    /**
     * Base constructor.
     * @param App|null $app
     */
    public function __construct(App $app = null)
    {
        parent::__construct($app);
    }

}
